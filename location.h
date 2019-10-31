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
};

map<string, location> parseLocations(string);
