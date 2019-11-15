#include "location.h"
#include <locale>

std::ostream& operator<<(std::ostream &strm, const location &l) {
	  return strm << l.description;
}

/* parseLocations returns a mapping from the unique ID of a location
 * to the object that represents that location.
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
	ifstream locFile(filename.c_str());
	//locFile.open(filename.c_str());
	string line;
	map<string, location> locations;
	location loc;

	if (locFile.is_open()) {
		while (getline(locFile, line)) {
			cout << line << endl;
			if (line == "") {
			} else if (line =="begin-location") {
			   getline(locFile, line);
			   loc.uid = line;
			   getline(locFile, line);
			   loc.name = line;
			   cout << loc.uid << endl << loc.name << endl;
			} else if (line =="begin-description") {
				loc.description = "";
				getline(locFile, line);
				cout << line << endl;
				while (line != "end-description") {
					cout << line << endl;
					loc.description += line + "\n";
					getline(locFile, line);
				}
			} else if (line == "begin-exits") {
				map<string,string> exits;
				getline(locFile, line);
				while (line != "end-exits") {
					string uid = line;
					string description;
					getline(locFile, description);
					
					int start = description.find(uid);
					if (start != string::npos) {
						description.replace(start, uid.length(), "\e[93m" + uid + "\e[0m");
					}
					
					exits[uid] = description;
					
					getline(locFile, line);
				}
				loc.exits = exits;
			} else if (line == "begin-objects") {
				loc.objects = parseObjects(locFile);
				cout << "Set the objects\n";
			} else if (line =="end-location") {
				locations[loc.uid] = loc;
			} else {
				cout << "Unknown directive: " << line << endl;
			}
		}
	}

	cout << "Closing file\n";

	locFile.close();

	return locations;
}

/* parseObjects is a helper function called by parseLocations
 * It receives the stream being read and begins parsing where
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
 * end-object
 */
map<string, object> parseObjects(ifstream& objFile) {
	string line;
	map<string,object> objects;

	if (objFile.is_open()) {
		getline(objFile, line);
		while (line != "end-objects") {
			//cout << line << endl;

			if (line == "begin-object") {
				object obj;

				cout << "Parsing the object\n";
					cout << line << endl;
				getline(objFile, line);
				obj.uid = line;
				getline(objFile, line);
				obj.name = line;
				cout << "Object: " << obj.uid << ", " << obj.name << endl;

				getline(objFile, line);

				while (line != "end-object") {
					cout << line << endl;
					if (line == "") {
					} else if (line =="begin-description") {
						obj.description = "";
						//cout << line << endl;
						getline(objFile, line);
						while (line != "end-description") {
							cout << line << endl;
							obj.description += line + "\n";
							getline(objFile, line);
						}
						cout << "exited desc\n";
					} else if (line == "points") {
						getline(objFile, line);
						obj.points = stoi(line);
					} else {
						cout << "Unknown directive: " << line << endl;
					}
					getline(objFile, line);
				}
				objects[obj.uid] = obj;
			}
			cout << "Added the object\n";
			getline(objFile, line);
		}
	}

	return objects;
}
