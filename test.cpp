#include <chrono>
#include <thread>

#include "location.h"
#include "getch.h"

#define move_up(rows) std::cout << "\e[" #rows "A"
#define move_down(rows) std::cout << "\e[" #rows "B"
#define move_by(rows,columns) std::cout << "\e[" #rows "A\e[" #rows "C"
#define clear_display() std::cout << "\e[H\e[2J"
#define get_arrow() getch();getch();getch()

using namespace std;

void show_splash();
void start_game(string user, string current_location, map<string,location> locs);


int main(){
	//cout << "Running\n";
	map<string,location> locs;
	//cout << "Created map\n";

	locs = parseLocations("locs.dat");
	//cout << "Parsed map\n";

	//cout << locs["CCH"].description << endl;
	//cout << "Accessed map\n\n";

	//cout << locs["CCH"] << endl;

	//this_thread::sleep_for(chrono::milliseconds(500));
	//show_splash();
	
	start_game("brian", "CCH", locs);

	return 0;
}

void start_game(string user, string current_location, map<string,location> locs) {
	string input;
	do {
		location loc = locs[current_location];
		cout << "\e[H\e[2JCurrent Location:\n" <<  loc.description << endl;
		cout << "Exits:\n" << loc.list_exits() << endl;
		cout << "Objects:\n" << loc.list_objects() << endl;

		cout << "type an exit or object to interact:\n>> ";
		getline(cin, input);
		
		map<string,string>::iterator l = loc.exits.find(input);
		map<string,string>::iterator o = loc.objects.find(input);
		
		if (l != loc.exits.end()) {
			cout << "Moving to " << l->first << endl;
			current_location = l->first;
		} else if (o != loc.objects.end()) {
			cout << "Interacting with " << o->first << endl;
		} else {
			cout << "Unknown command \"" << input << "\"\n";
		}
	} while (input != "drop out");
}

void show_splash() {
	cout << "\e[H\e[2J";
	for (char c : "TAMU-CC") {
		cout << c << flush;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	/*for (int i = 0; i < 10; i++) {
		cout << i;
		this_thread::sleep_for(chrono::milliseconds(500));
		if (i%2) {
			cout << "\e[A\e[3D  ";
		} else {
			cout << "\n\e[" << i-2 << "C   ";
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}*/
}
