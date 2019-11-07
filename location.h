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
};

class location {
	public:
		string uid,
			   name,
			   description;
		map<string, string> exits;
		map<string, object> objects;
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

map<string, location> parseLocations(string);

map<string, object> parseObjects(ifstream&);
