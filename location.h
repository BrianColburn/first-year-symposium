#pragma once

#include <string>
#include <map>

#include <iostream>
#include <fstream>

using namespace std;

class location {
	public:
		string uid,
			   name,
			   description;
		map<string, string> exits;
		map<string, string> objects;
		friend std::ostream& operator<<(std::ostream&, const location&);

		string list_objects() {
			string result = "";
			for (map<string, string>::iterator object = objects.begin(); object != objects.end(); ++object) {
				result += "[" + object->first + "]: " +  object->second;
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
