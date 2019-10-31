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


int main(){
	cout << "Running\n";
	map<string,location> locs;
	cout << "Created map\n";

	locs = parseLocations("locs.dat");
	cout << "Parsed map\n";

	cout << locs["CCH"].description << endl;
	cout << "Accessed map\n\n";

	cout << locs["CCH"] << endl;

	this_thread::sleep_for(chrono::milliseconds(500));
	show_splash();

	return 0;
}

void start_game() {
	
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
