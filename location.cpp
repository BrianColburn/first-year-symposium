#include "location.h"
#include <locale>

std::ostream& operator<<(std::ostream &strm, const location &l) {
	  return strm << l.description;
}

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
				map<string,object> objects;
				getline(locFile, line);
				while (line != "end-objects") {
					object obj;

						while (line != "end-object") {
							cout << line << endl;
							if (line == "") {
							} else if (line =="begin-object") {
								cout << "Parsing the object\n";
							   getline(locFile, line);
							   obj.uid = line;
							   getline(locFile, line);
							   obj.name = line;
							   //cout << obj.uid << endl << obj.name << endl;
							} else if (line =="begin-description") {
								obj.description = "";
								//cout << line << endl;
								getline(locFile, line);
								while (line != "end-description") {
									obj.description += line + "\n";
									getline(locFile, line);
								}
								cout << "exited desc\n";
							} else {
								cout << "Unknown directive: " << line << endl;
							}
							getline(locFile, line);
						}
						objects[obj.uid] = obj;
						cout << "Added the object\n";
						getline(locFile, line);
				}
				loc.objects = objects;
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

map<string, object> parseObjects(ifstream objFile) {
	//objFile.open(filename.c_str());
	string line;
	map<string, object> objects;
	object obj;

	if (objFile.is_open()) {
		getline(objFile, line);
		while (line != "end-objects") {
			cout << line << endl;
			if (line == "") {
			} else if (line =="begin-object") {
				cout << "Parsing the object\n";
			   getline(objFile, line);
			   obj.uid = line;
			   getline(objFile, line);
			   obj.name = line;
			   cout << obj.uid << endl << obj.name << endl;
			} else if (line =="begin-description") {
				obj.description = "";
				getline(objFile, line);
				cout << 1 << line << endl;
				while (line != "end-description") {
					cout << 2 << line << endl;
					obj.description += line + "\n";
					getline(objFile, line);
				}
			} else {
				cout << "Unknown directive: " << line << endl;
			}
			getline(objFile, line);
		}
	}

	return objects;
}
