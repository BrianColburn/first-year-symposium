#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

#include "location.h"
#include "getch.h"

#define move_up(rows) std::cout << "\e[" #rows "A"
#define move_down(rows) std::cout << "\e[" #rows "B"
#define move_by(rows,columns) std::cout << "\e[" #rows "A\e[" #rows "C"
#define clear_display() std::cout << "\e[H\e[2J"
#define get_arrow() getch();getch();getch()

using namespace std;

// These are here so that the compiler knows these functions will be defined later.
void show_splash();
void menu(map<string,location> locs);
void highscores();
void credits();
void start_game(string user, string current_location, map<string,location> locs);


// `main' is what is called when the program is run
int main(){
	cout << "Running\n"; // Make sure we aren't going crazy, it actually is running.
	map<string,location> locs; // This reserves space for a lookup table (a map)
	                           //   from the name of a location to the data for that location.
	//cout << "Created map\n";

	locs = parseLocations("locs.dat"); // We fill the map with the information in the
	                                   //   file "locs.dat". `parseLocations' is defined
									   //   in the file "location.cpp".
	cout << "Parsed map\n"; // We aren't crazy, if something goes wrong we got this far at least.

	//cout << locs["CCH"].description << endl;
	//cout << "Accessed map\n\n";

	//cout << locs["CCH"] << endl;

	std::cout << "Displaying splash!" << '\n'; // Still sane!
	show_splash(); // Call the function `show_splash', which does what you think it does.
	menu(locs); // Display the menu. We pass the location data to it since it's needed
	            //   if the user wants to actually play the game.

	

	return 0;
}

/* start_game functions as the main game loop.
 * It handles the interaction between the user and the locations.
 */
void start_game(string user, string current_location, map<string,location> locs) {
	int points = 0; // Set the player's points to 0.
	string input; // Reserve space for storing the user's input.
	int loop = 0; // How long has the player been in this location?

	getch(); // Wait for the user to press any key.
	cout << "\e[H\e[2J";
	do {
		location loc = locs[current_location]; // This basically just saves typing.

		if (!loop && loc.directive != "") { // If we haven't looped and there is a directive, 
			cout << loc.directive << "\n..."; // display the directive and wait.
			getch();
		}

		//Tell the player where they are, where they can go, and what they can touch.
		cout << "\e[H\e[2JName: " << user << "    Points: " << points << endl;
		cout << "Current Location: " << loc.name << endl <<  loc.description << endl;
		cout << "Exits:\n" << loc.list_exits() << endl;
		cout << "Objects:\n" << loc.list_objects() << endl;

		cout << "type an exit or object to interact:\n>> ";
		getline(cin, input); // Wait for the player to enter a command.

		// Determine if the user meant to interact with their
		// environment. Prefaced with 'p' since they are "possible" results.
		map<string,string>::iterator pExit = loc.exits.find(input);
		map<string,object>::iterator pObj = loc.objects.find(input);
    
		if (pExit != loc.exits.end()) {
			cout << "Moving to " << pExit->first << endl; // Not crazy, we are moving.
			current_location = pExit->first; // Change our current location.
			                                 //   This will take effect on the next game tick.
			loop = -1; // Becomes zero when we loop into the new location.
		}

		else if (pObj != loc.objects.end()) {
			object obj = pObj->second; // The object does exist, so we get its info.
			cout << "Interacting with " << pObj->first << endl; // Sane

			if (obj.points) { // We check if the object is worth any points.
				              //   If it is, then we add them to the score and
							  //   tell the user.
				cout << "You gained " << obj.points << " points!\n";
				points += obj.points;
				cout << "You now have " << points << " points.\n";
			}

			if (obj.uses > 0) { // Check if the object has a limited number of uses.
				obj.uses--; // Decrease the remaining uses.
				
				if (!obj.uses) { // No more uses
					locs[current_location].objects.erase(obj.uid);
				}
			}

			cout << "...\n";
			getch(); // Wait for a keypress

			if (obj.directive != "") {
				cout << obj.directive << "\n...";
				getch();
			}
		}

		else if (input == "contribute") {
			cout << "\e[H\e[2JWhat would you like to contribute?\n"
				    "1) A Note\n"
				    "2) An Object\n"
				    "3) A Location\n"
					"(otherwise, cancel)\n"
				    "\n>> ";
			char choice = getch();
			cout << "\e[H\e[2J";

			switch (choice) {
				case '1': {
					string message = "";
					cout << "What would you like to write on the note? (Enter a '.' on an empty line to stop writing)\n"
						    "Note from " << user << ":\n";
					do {
						cout << "> ";
						getline(cin, input);
						if (input != ".")
							message += "> " + input + "\n";
							// The '>' is to protect against injection attacks.
							// Such as "end-directive<enter>LOCATION CODE"
					} while (input != ".");

					ifstream oldLocFile("locs.dat");
					ofstream newLocFile("new-locs.dat");
					string currentLine = "";
					
					// Skip through the file until we find our current location.
					while (getline(oldLocFile, currentLine) && currentLine != current_location)
						newLocFile << currentLine << endl;
					newLocFile << currentLine << endl; // Add the location ID.
					// Skip through the file until we begin defining objects.
					while (getline(oldLocFile, currentLine) && currentLine != "begin-objects")
						newLocFile << currentLine << endl;
					newLocFile << currentLine << endl; // Add the "begin-objects"

					// Now we add the note as an object.
					newLocFile << "begin-object\n"
					           << user << "'s note\n"
							   << "note name\n"
							   << "begin-description\n"
							   << "A note from " << user << endl
							   << "end-description\n"
							   << "begin-directive\n"
							   << message << endl
							   << "end-directive\n"
							   << "end-object\n";

					// Write the rest of the file.
					while (getline(oldLocFile, currentLine))
							newLocFile << currentLine << endl;

					points += 2;
					oldLocFile.close();
					newLocFile.close();
					system("mv locs.dat \"locs.dat.bk.$(date +'%H%M%S')\"");
					system("mv new-locs.dat locs.dat");

					break;
				}

				case '2': {
					object obj;
					cout << "Enter an ID for the object: ";
					getline(cin, input);
					
					while (input.substr(0,6) == "begin-" || input.substr(0,4) == "end-") {
						cout << "ID's cannot contain \"begin-\" or \"end-\"";
						cout << "Enter an ID for the object: ";
						getline(cin, input);
					}
					obj.uid = input;

					cout << "Enter a description for the object. Type '.' to finish.";
					do {
						cout << "> ";
						getline(cin, input);
						if (input != ".")
							obj.description += " " + input + "\n";
							// The ' ' is to protect against injection attacks.
							// Such as "end-directive<enter>LOCATION CODE"
					} while (input != ".");

					cout << "Does this object have a directive? [y/N]\n";
					choice = getch();
					if ((choice & 95) == 'Y') {
						cout << "Enter the directive for the object. Type '.' to finish.\n";
						do {
							cout << "> ";
							getline(cin, input);
							if (input != ".")
								obj.directive += "> " + input + "\n";
								// The '>' is to protect against injection attacks.
								// Such as "end-directive<enter>LOCATION CODE"
						} while (input != ".");
					}

					cout << "Does this object have a limited number of uses? [y/N]\n";
					choice = getch();
					if ((choice & 95) == 'Y') {
						cout << "Enter the number of uses: ";
						getline(cin, input);
						obj.uses = stoi(input);
					}

					cout << "Is this object worth any points? [y/N]\n";
					choice = getch();
					if ((choice & 95) == 'Y') {
						cout << "Enter the number of points (up to " << points << "): ";
						getline(cin, input);
						obj.points = stoi(input);
						if (obj.points > points)
							obj.points = points;
					}

					ifstream oldLocFile("locs.dat");
					ofstream newLocFile("new-locs.dat");
					string currentLine = "";
					
					// Skip through the file until we find our current location.
					while (getline(oldLocFile, currentLine) && currentLine != current_location)
						newLocFile << currentLine << endl;
					newLocFile << currentLine << endl; // Add the location ID.
					// Skip through the file until we begin defining objects.
					while (getline(oldLocFile, currentLine) && currentLine != "begin-objects")
						newLocFile << currentLine << endl;
					newLocFile << currentLine << endl; // Add the "begin-objects"

					// Now we add the note as an object.
					newLocFile << "begin-object\n"
					           << obj.uid << endl
							   << "redundant" << endl
							   << "begin-description\n"
							   << obj.description
							   << "end-description\n"
							   << "begin-directive\n"
							   << obj.directive
							   << "end-directive\n"
							   << "points\n"
							   << obj.points << endl
							   << "uses\n"
							   << obj.uses << endl
							   << "end-object\n";

					// Write the rest of the file.
					while (getline(oldLocFile, currentLine))
							newLocFile << currentLine << endl;

					points += 20;
					oldLocFile.close();
					newLocFile.close();
					system("mv locs.dat \"locs.dat.bk.$(date +'%H%M%S')\"");
					system("mv new-locs.dat locs.dat");

					break;
				}

				case '3': {
					break;
				}
			}
		}

		else { // We have determined that the player did not type the name of
			   //   an exit or an object. Now we check if they meant something
			   //   more complex.

			// We seperate what the player entered into each word.
			vector<string> vinput; // Called "vinput" since it is a vector of the input.
			stringstream ss(input);
			string tmp;
			while (ss >> tmp) vinput.push_back(tmp); // Add each word to the list

			// Check if the input matches "add exit ANYTHING"
			if (vinput.size() == 3 && vinput[0] == "add" && vinput[1] == "exit") {
				// Create an exit leading from the current location to the exit
				//   the player specified.
				locs[current_location].exits[vinput[2]] = "Custom exit";
				cout << loc.list_exits();
			}
			// We don't know what to do with the player's input.
			else cout << "Unknown command \"" << input << "\"\n";
		}
		loop++;
	} while (input != "quit"); // If they want to quit, stop the game loop.

	char leaveScore; // Set aside space for a letter.
	cout << "Do you want to save your score? (Y/n)\n";
	leaveScore = getch(); // Get the letter entered by the user.
	if ((leaveScore & 95) == 'Y') { // the "&95" bit converts lowercase letters
		                            // to uppercase
		string scoreName; // Set aside space for some text
		cout << "Please enter a three letter name: ";
		cin >> scoreName;
		scoreName = scoreName.substr(0,3); // Only take the first three letters
		cout << setw(2) << points << ":  " << scoreName << endl; // Display their score entry
		ofstream ofscores("highscores.dat", ios_base::app); // Open up the high score file
		ofscores << points << " " << scoreName << endl; // Append the player's score
	}
	cout << "\n\nHigh Scores:\n";
	highscores(); // Display all the other high scores.
}

// Show the amazing 32 frame splash screen.
void show_splash() {
	// This is simply a list containing each frame for the splash screen.
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

	for (int i = 0; i < 32; i++) { // Loop through each frame
		cout << "\e[H\e[2J"; // Clear the previous frame
		cout << frame[i]; // Display the current frame
		this_thread::sleep_for(chrono::milliseconds(80)); // Give the user time to
		                                                  //   appreciate each frame.
	}
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

	char choice; // Reserve space for the user's choice
	string tmp; // Reserve space for user's name
	do {
		choice = getch();

		switch (choice) // Figure out what the user wants to do.
		{
			case '1': // They want to play the game
				cout << "\nEnter your name: ";
				cin >> tmp;
				start_game(tmp, "PAC", locs);
				break;
			case '2': // They want to view the high scores
				highscores();
				break;
			case '3': // They want to view the credits
				credits();
				break;
			case '4': // They want to leave
				cout << "Have a great day!\n";
				break;
			default: // They don't know what they want
				cout << "You don't seem to have entered a valid choice!";
		}
	} while (choice < '1' || choice > '4');
}

//Displays the credits
void credits() {
	cout << "The credits\n";
}

void highscores() {
	// Open the high score file and reserve variables for reading it.
	ifstream ifscores("highscores.dat");
	vector<pair<int,string>> vscores;
	string tmp;

	// Read each score into a pair and store that pair in a list.
	// The result looks like {(score1, name1), (score2, name2) ...}
	while (ifscores >> tmp) {
		pair<int,string> entry;
		entry.first = stoi(tmp);
		ifscores >> tmp;
		entry.second = tmp;
		vscores.push_back(entry);
	}

	sort(vscores.begin(), vscores.end()); // Sort the scores to lowest to highest
	reverse(vscores.begin(), vscores.end()); // Reverse them to make it highest to lowest.

	for (int i = 0; i < vscores.size(); i++) { // Loop through each score and display it.
		cout << setw(2) << vscores[i].first << ":  " << vscores[i].second << endl;
	}
}
