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
	cout << "Running\n";
	map<string,location> locs;
	//cout << "Created map\n";

	locs = parseLocations("locs.dat");
	cout << "Parsed map\n";

	//cout << locs["CCH"].description << endl;
	//cout << "Accessed map\n\n";

	//cout << locs["CCH"] << endl;

	std::cout << "Displaying splash!" << '\n';
	show_splash();
	this_thread::sleep_for(chrono::milliseconds(1000));

	start_game("brian", "CCH", locs);

	return 0;
}

/* start_game currently functions as the main loop.
 * It handles the interaction between the user and the locations.
 */
void start_game(string user, string current_location, map<string,location> locs) {
	string input;
	do {
		location loc = locs[current_location];
		cout << "\e[H\e[2JCurrent Location:\n" <<  loc.description << endl;
		cout << "Exits:\n" << loc.list_exits() << endl;
		cout << "Objects:\n" << loc.list_objects() << endl;

		cout << "type an exit or object to interact:\n>> ";
		getline(cin, input);

		// Determine if the user meant to interact with their
		// environment.
		map<string,string>::iterator l = loc.exits.find(input);
		map<string,object>::iterator o = loc.objects.find(input);
    
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

// Show the amazing 32 frame splash screen.
void show_splash() {
	string frame[32] = {
		"  ___            \n |__ \\\n   / /\n  |_|\n  (_)\n",
		"  ___             ___ \n |__ \\           |__ \\\n   / /             / /\n  |_|             |_| \n  (_)             (_) \n",
		"  ___            ___ \n |__ \\          |__ \\\n   / /            / /\n  |_|            |_| \n  (_)            (_) \n" ,
		"  ___           ___ \n |__ \\         |__ \\\n   / /           / /\n  |_|           |_| \n  (_)           (_) \n" ,
		"  ___          ___ \n |__ \\        |__ \\\n   / /          / /\n  |_|          |_| \n  (_)          (_) \n" ,
		"  ___         ___ \n |__ \\       |__ \\\n   / /         / /\n  |_|         |_| \n  (_)         (_) \n" ,
		"  ___        ___ \n |__ \\      |__ \\\n   / /        / /\n  |_|        |_| \n  (_)        (_) \n" ,
		"  ___       ___ \n |__ \\     |__ \\\n   / /       / /\n  |_|       |_| \n  (_)       (_) \n" ,
		"  ___      ___ \n |__ \\    |__ \\\n   / /      / /\n  |_|      |_| \n  (_)      (_) \n" ,
		"  ___     ___ \n |__ \\   |__ \\\n   / /     / /\n  |_|     |_| \n  (_)     (_) \n" ,
		"  ___    ___ \n |__ \\  |__ \\\n   / /    / /\n  |_|    |_| \n  (_)    (_) \n" ,
		"  ___    ___             ___ \n |__ \\  |__ \\           |__ \\\n   / /    / /             / /\n  |_|    |_|             |_| \n  (_)    (_)             (_) \n" ,
		"  ___    ___            ___ \n |__ \\  |__ \\          |__ \\\n   / /    / /            / /\n  |_|    |_|            |_| \n  (_)    (_)            (_) \n" ,
		"  ___    ___           ___ \n |__ \\  |__ \\         |__ \\\n   / /    / /           / /\n  |_|    |_|           |_| \n  (_)    (_)           (_) \n" ,
		"  ___    ___          ___ \n |__ \\  |__ \\        |__ \\\n   / /    / /          / /\n  |_|    |_|          |_| \n  (_)    (_)          (_) \n" ,
		"  ___    ___         ___ \n |__ \\  |__ \\       |__ \\\n   / /    / /         / /\n  |_|    |_|         |_| \n  (_)    (_)         (_) \n" ,
		"  ___    ___        ___ \n |__ \\  |__ \\      |__ \\\n   / /    / /        / /\n  |_|    |_|        |_| \n  (_)    (_)        (_) \n" ,
		"  ___    ___       ___ \n |__ \\  |__ \\     |__ \\\n   / /    / /       / /\n  |_|    |_|       |_| \n  (_)    (_)       (_) \n" ,
		"  ___    ___      ___ \n |__ \\  |__ \\    |__ \\\n   / /    / /      / /\n  |_|    |_|      |_| \n  (_)    (_)      (_) \n" ,
		"  ___    ___     ___ \n |__ \\  |__ \\   |__ \\\n   / /    / /     / /\n  |_|    |_|     |_| \n  (_)    (_)     (_) \n" ,
		"  ___    ___    ___ \n |__ \\  |__ \\  |__ \\\n   / /    / /    / /\n  |_|    |_|    |_| \n  (_)    (_)    (_) \n" ,
		"  ___    ___    ___             ___ \n |__ \\  |__ \\  |__ \\           |__ \\\n   / /    / /    / /             / /\n  |_|    |_|    |_|             |_| \n  (_)    (_)    (_)             (_) \n" ,
		"  ___    ___    ___            ___ \n |__ \\  |__ \\  |__ \\          |__ \\\n   / /    / /    / /            / /\n  |_|    |_|    |_|            |_| \n  (_)    (_)    (_)            (_) \n" ,
		"  ___    ___    ___           ___ \n |__ \\  |__ \\  |__ \\         |__ \\\n   / /    / /    / /           / /\n  |_|    |_|    |_|           |_| \n  (_)    (_)    (_)           (_) \n" ,
		"  ___    ___    ___          ___ \n |__ \\  |__ \\  |__ \\        |__ \\\n   / /    / /    / /          / /\n  |_|    |_|    |_|          |_| \n  (_)    (_)    (_)          (_) \n" ,
		"  ___    ___    ___         ___ \n |__ \\  |__ \\  |__ \\       |__ \\\n   / /    / /    / /         / /\n  |_|    |_|    |_|         |_| \n  (_)    (_)    (_)         (_) \n" ,
		"  ___    ___    ___        ___ \n |__ \\  |__ \\  |__ \\      |__ \\\n   / /    / /    / /        / /\n  |_|    |_|    |_|        |_| \n  (_)    (_)    (_)        (_) \n" ,
		"  ___    ___    ___       ___ \n |__ \\  |__ \\  |__ \\     |__ \\\n   / /    / /    / /       / /\n  |_|    |_|    |_|       |_| \n  (_)    (_)    (_)       (_) \n" ,
		"  ___    ___    ___      ___ \n |__ \\  |__ \\  |__ \\    |__ \\\n   / /    / /    / /      / /\n  |_|    |_|    |_|      |_| \n  (_)    (_)    (_)      (_) \n" ,
		"  ___    ___    ___     ___ \n |__ \\  |__ \\  |__ \\   |__ \\\n   / /    / /    / /     / /\n  |_|    |_|    |_|     |_| \n  (_)    (_)    (_)     (_) \n" ,
		"  ___    ___    ___    ___ \n |__ \\  |__ \\  |__ \\  |__ \\\n   / /    / /    / /    / /\n  |_|    |_|    |_|    |_| \n  (_)    (_)    (_)    (_) \n" ,
		"  ___            ___  ___      ___  ____   _______ _____ _____________   __\n / _ \\    ___    |  \\/  |      |  \\/  \\ \\ / /  ___|_   _|  ___| ___ \\ \\ / /\n/ /_\\ \\  ( _ )   | .  . |      | .  . |\\ V /\\ `--.  | | | |__ | |_/ /\\ V / \n|  _  |  / _ \\/\  | |\\/| |      | |\\/| | \\ /  `--. \\ | | |  __||    /  \\ /  \n| | | | | (_>  < | |  | |      | |  | | | | /\\__/ / | | | |___| |\\ \\  | |  \n\\_| |_/  \\___/\\/ \\_|  |_/      \\_|  |_/ \\_/ \\____/  \\_/ \\____/\\_| \\_| \\_/\n",
	};

	for (int i = 0; i < 32; i++) {
		cout << "\e[H\e[2J";
		cout << frame[i];
		this_thread::sleep_for(chrono::milliseconds(80));}
}
