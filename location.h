#pragma once

#include <string>
#include <map>

#include <iostream>
#include <fstream>

using namespace std;

class object {
	public:
		string uid,
			   name,
			   description;
		int points = 0;
};

class location {
	public:
		string uid,
			   name,
			   description,
			   directive;
		map<string, string> exits; // maps from the exit UID to
		                           // the local description of that exit.
		map<string, object> objects; // maps from the object ID to
		                             // the local representation of that
									 // object
		friend std::ostream& operator<<(std::ostream&, const location&);

		string list_objects() {
			string result = "";
			for (map<string, object>::iterator object = objects.begin(); object != objects.end(); ++object) {
				result += "[" + object->first + "]: " +  object->second.description;
				result += "\n";
			}
			return result;
		}

		string list_exits() {
			string result = "";
			for (map<string, string>::iterator exit = exits.begin(); exit != exits.end(); ++exit) {
				result += "[" + exit->first + "]: " + exit->second;
				result += "\n";
			}
			return result;
		}
};

// Parse the locations stored in a given file.
map<string, location> parseLocations(string);

// Parse the objects stored in a given stream.
// Called by parseLocations
map<string, object> parseObjects(ifstream&);
