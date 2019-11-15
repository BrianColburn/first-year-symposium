#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>

#include "location.h"
#include "getch.h"

#define move_up(rows) std::cout << "\e[" #rows "A"
#define move_down(rows) std::cout << "\e[" #rows "B"
#define move_by(rows,columns) std::cout << "\e[" #rows "A\e[" #rows "C"
#define clear_display() std::cout << "\e[H\e[2J"
#define get_arrow() getch();getch();getch()

using namespace std;

void show_splash();
void menu(map<string,location> locs);
void highscores();
void credits();
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
	menu(locs);

	

	return 0;
}

void start_game(string user, string current_location, map<string,location> locs) {
	int points = 0;
	string input;
	getline(cin, input);
	cout << "You must make your way to corpus Christi Hall (CCH) and register for classes!\n...";
	getch();
	do {
		location loc = locs[current_location];
		cout << "\e[H\e[2JCurrent Location:\n" <<  loc.description << endl;
		cout << "Exits:\n" << loc.list_exits() << endl;
		cout << "Objects:\n" << loc.list_objects() << endl;

		cout << "type an exit or object to interact:\n>> ";
		getline(cin, input);

		map<string,string>::iterator l = loc.exits.find(input);
		map<string,object>::iterator o = loc.objects.find(input);
    
		if (l != loc.exits.end()) {
			cout << "Moving to " << l->first << endl;
			current_location = l->first;
		} else if (o != loc.objects.end()) {
			object obj = o->second;
			cout << "Interacting with " << o->first << endl;
			if (obj.points) {
				cout << "You gained " << obj.points << " points!\n";
				points += obj.points;
				cout << "You now have " << points << " points.\n";
			}
			getch();
		} else {
			vector<string> vinput;
			stringstream ss(input);
			string tmp;
			while (ss >> tmp) vinput.push_back(tmp);

			if (vinput.size() > 0 && vinput[0] == "add" && vinput[1] == "exit") {
				locs[current_location].exits[vinput[2]] = "Custom exit";
				cout << loc.list_exits();
			} else
				cout << "Unknown command \"" << input << "\"\n";
		}
	} while (input != "quit");
	char leaveScore;
	cout << "Do you want to save your score? (Y/n)\n";
	leaveScore = getch();
	if ((leaveScore & 95) == 'Y') {
		string scoreName;
		cout << "Please enter a three letter name: ";
		cin >> scoreName;
		scoreName = scoreName.substr(0,3);
		cout << setw(2) << points << ":  " << scoreName << endl;
		ofstream ofscores("highscores.dat", ios_base::app);
		ofscores << points << " " << scoreName << endl;
	}
	cout << "\n\nHighscores:\n";
	highscores();
}

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

void menu(map<string,location> locs) {
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "WELCOME TO THE GAME, PLAYER!\n";
	cout << "TO BEGIN, JUST SELECT ONE OF THE MENU OPTIONS \n";
	cout << "BY SELECTING THE CORRESPONDING NUMBERS!";
	cout << "\n";
	cout << "\n";
	cout << "	1. start\n";
	cout << "\n";
	cout << "	2. highscores\n";
	cout << "\n";
	cout << "	3. credits\n";
	cout << "\n";
	cout << "	4. exit\n";
	cout << "\n";

	char choice;
	string tmp;
	do {
		choice = getch();

		switch (choice)
		{
			case '1': 
				cout << "\nEnter your name: ";
				cin >> tmp;
				start_game(tmp, "CCH", locs);
				break;
			case '2':
				highscores();
				break;
			case '3':
				credits();
				break;
			case '4':
				cout << "Have a great day!\n";
				break;
			default:
				cout << "You don't seem to have entered a valid choice!";
		}
	} while (choice < '1' || choice > '4');
}

void credits() {
	cout << "The credits\n";
}

void highscores() {
	ifstream ifscores("highscores.dat");
	vector<pair<int,string>> vscores;
	string tmp;
	while (ifscores >> tmp) {
		pair<int,string> entry;
		entry.first = stoi(tmp);
		ifscores >> tmp;
		entry.second = tmp;
		vscores.push_back(entry);
	}
	sort(vscores.begin(), vscores.end());
	reverse(vscores.begin(), vscores.end());
	for (int i = 0; i < vscores.size(); i++) {
		cout << setw(2) << vscores[i].first << ":  " << vscores[i].second << endl;
	}
}
