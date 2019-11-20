#include "location.h"
#include <locale>

std::ostream& operator<<(std::ostream &strm, const location &l) {
	  return strm << l.description;
}

/* parseLocations returns an association (a mapping) from the unique ID of a location
 * to information that represents that location.
 *
 *
 * The format for location files is this:
 *
 * begin-location
 * $uid
 * $name
 * begin-description
 * $description
 * end-description
 * begin-exits
 * $exit-uid
 * $exit-local-description
 * ...
 * end-exits
 * begin-objects
 * $OBJECT FORMAT
 * end-objects
 * end-location
 *
 * objects are parsed with the function parseObjects
 */
map<string, location> parseLocations(string filename) {
	ifstream locFile(filename.c_str()); // Open the filename passed to this function
	//locFile.open(filename.c_str());
	string line; // Reserve a variable to read each line into
	map<string, location> locations; // Create an empty map
	location loc; // Create an empty location

	if (locFile.is_open()) { // Make sure the file exists
		while (getline(locFile, line)) { // Loop until the end of the file
			cout << line << endl; // Sanity check
			
			if (line == "") { // Ignore blank lines
			}
			
			else if (line =="begin-location") { // Read in the ID and name of the
				                                  //   location.
				getline(locFile, line);
				loc.uid = line;
				getline(locFile, line);
				loc.name = line;
				cout << loc.uid << endl << loc.name << endl;
				loc.directive = "";
				map<string,object> empty;
				loc.objects = empty;
			}
			
			else if (line =="begin-description") {
				loc.description = ""; // Prepare the location's description
				getline(locFile, line); // Read the line from the description
				cout << line << endl;
				while (line != "end-description") { // Append and read each line to
					                                //   the description until it
													//   reaches a line that contains
													//   only "end-description".
					cout << line << endl;
					loc.description += line + "\n";
					getline(locFile, line);
				}
			}

			else if (line =="directive") { // This location has a directive
				getline(locFile, line);
				loc.directive = line;
			}
			
			else if (line == "begin-exits") {
				map<string,string> exits; // Prepare an empty map for the exits.
				                          //   The map associates the UID for an exit
				                          //   with the local description of the exit.
				getline(locFile, line);
				while (line != "end-exits") {
					string uid = line;
					string description;
					getline(locFile, description);
					
					int start = description.find(uid); // Search the description of the exit
					                                   //   for the exit's UID.
					                                   //   If it's found, highlight it.
					if (start != string::npos) {
						description.replace(start, uid.length(), "\e[93m" + uid + "\e[0m");
					}
					
					exits[uid] = description;
					
					getline(locFile, line);
				}
				loc.exits = exits;
			}
			
			else if (line == "begin-objects") {
				loc.objects = parseObjects(locFile); // Let `parseObjects' do the
				                                     //   heavy lifting.
				cout << "Set the objects\n"; // Still sane.
			}
			
			else if (line =="end-location") { // We've hit the end of this location's
			                                  //   data, and can add it to the map.
				locations[loc.uid] = loc;
			}
			
			else { // Something's gone wrong, but we might not want to just crash.
				cout << "Unknown directive: " << line << endl;
			}
		}
	}

	cout << "Closing file\n"; // Sane

	locFile.close();

	return locations;
}

/* parseObjects is a helper function called by parseLocations
 * It receives the file stream being read and begins parsing where
 * parseLocations left off and returns a mapping from the
 * non-unique id of an object to the representation of that
 * object.
 *
 * 
 * The format for object definitions is:
 * 
 * begin-object
 * $id
 * $name
 * begin-description
 * $description
 * end-description
 * points
 * $points
 * end-object
 */
map<string, object> parseObjects(ifstream& objFile) {
	string line;
	map<string,object> objects;

	if (objFile.is_open()) {
		getline(objFile, line);
		while (line != "end-objects") { // Loop until we reach the end of the objects
			//cout << line << endl;

			if (line == "begin-object") { // We're defining a new object
				object obj;

				cout << "Parsing the object\n"; // Sanity
				cout << line << endl;
				
				getline(objFile, line);
				obj.uid = line;
				getline(objFile, line);
				obj.name = line;

				// One can never be too sane.
				cout << "Object: " << obj.uid << ", " << obj.name << endl;

				getline(objFile, line);

				while (line != "end-object") { // Loop until we're done with this object.
					cout << line << endl; // Such sanity
					if (line == "") {
					}
					
					else if (line =="begin-description") { // Same thing as location descriptions.
						obj.description = "";
						//cout << line << endl;
						getline(objFile, line);
						while (line != "end-description") {
							cout << line << endl; // Not insane
							obj.description += line + "\n";
							getline(objFile, line);
						}

						int start = obj.description.find(obj.uid); // Search the description of the exit
																   //   for the exit's UID.
																   //   If it's found, highlight it.
						if (start != string::npos) {
							obj.description.replace(start, obj.uid.length(), "\e[32m" + obj.uid + "\e[0m");
						}

						cout << "exited desc\n"; // Still doing okay.
					}
					
					else if (line == "points") { // This object is worth something.
						getline(objFile, line);
						obj.points = stoi(line); // Convert the value from text to an integer.
					}
					
					else if (line == "uses") { // This object has a limited number of uses.
						getline(objFile, line);
						obj.uses = stoi(line); // Convert the value from text to an integer.
					}
					
					else if (line == "directive") { // This object has a directive.
						getline(objFile, line);
						obj.directive = line;
					}
					
					else { // Apparently we aren't sane.
						cout << "Unknown directive: " << line << endl;
					}
					getline(objFile, line);
				}

				objects[obj.uid] = obj; // We can add the object to the map.
			}

			cout << "Added the object\n"; // Sane
			getline(objFile, line); // See what we should do next.
		}
	}

	return objects; // `parseObjects' has done its job and can return its results.
}
