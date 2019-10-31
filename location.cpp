#include "location.h"

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
			//cout << line << endl;
			if (line =="begin-location") {
			   getline(locFile, line);
			   loc.uid = line;
			   getline(locFile, line);
			   loc.name = line;
			   //cout << loc.uid << endl << loc.name << endl;
			}
			else if (line =="begin-description") {
				getline(locFile, line);
				//cout << line << endl;
				while (line != "end-description") {
					//cout << line << endl;
					loc.description += line + "\n";
					getline(locFile, line);
				}
			}
			else if (line =="end-location") {
				locations[loc.uid] = loc;
			} else {
				cout << "Unknown directive: " << line << endl;
			}
		}
	}

	//cout << "Closing file\n";

	locFile.close();

	return locations;
}
