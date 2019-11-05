#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
int main ()
{
string frame1 = "  ___            \n |__ \\\n   / /\n  |_|\n  (_)\n";


string frame2 = "  ___             ___ \n |__ \\           |__ \\\n   / /             / /\n  |_|             |_| \n  (_)             (_) \n" ;


string frame3 = "  ___            ___ \n |__ \\          |__ \\\n   / /            / /\n  |_|            |_| \n  (_)            (_) \n" ;


string frame4 = "  ___           ___ \n |__ \\         |__ \\\n   / /           / /\n  |_|           |_| \n  (_)           (_) \n" ;


string frame5 = "  ___          ___ \n |__ \\        |__ \\\n   / /          / /\n  |_|          |_| \n  (_)          (_) \n" ;


string frame6 = "  ___         ___ \n |__ \\       |__ \\\n   / /         / /\n  |_|         |_| \n  (_)         (_) \n" ;


string frame7 = "  ___        ___ \n |__ \\      |__ \\\n   / /        / /\n  |_|        |_| \n  (_)        (_) \n" ;


string frame8 = "  ___       ___ \n |__ \\     |__ \\\n   / /       / /\n  |_|       |_| \n  (_)       (_) \n" ;


string frame9 = "  ___      ___ \n |__ \\    |__ \\\n   / /      / /\n  |_|      |_| \n  (_)      (_) \n" ;


string frame10 = "  ___     ___ \n |__ \\   |__ \\\n   / /     / /\n  |_|     |_| \n  (_)     (_) \n" ;


string frame11 = "  ___    ___ \n |__ \\  |__ \\\n   / /    / /\n  |_|    |_| \n  (_)    (_) \n" ;


string frame12 = "  ___    ___             ___ \n |__ \\  |__ \\           |__ \\\n   / /    / /             / /\n  |_|    |_|             |_| \n  (_)    (_)             (_) \n" ;


string frame13 = "  ___    ___            ___ \n |__ \\  |__ \\          |__ \\\n   / /    / /            / /\n  |_|    |_|            |_| \n  (_)    (_)            (_) \n" ;


string frame14 = "  ___    ___           ___ \n |__ \\  |__ \\         |__ \\\n   / /    / /           / /\n  |_|    |_|           |_| \n  (_)    (_)           (_) \n" ;


string frame15 = "  ___    ___          ___ \n |__ \\  |__ \\        |__ \\\n   / /    / /          / /\n  |_|    |_|          |_| \n  (_)    (_)          (_) \n" ;


string frame16 = "  ___    ___         ___ \n |__ \\  |__ \\       |__ \\\n   / /    / /         / /\n  |_|    |_|         |_| \n  (_)    (_)         (_) \n" ;


string frame17 = "  ___    ___        ___ \n |__ \\  |__ \\      |__ \\\n   / /    / /        / /\n  |_|    |_|        |_| \n  (_)    (_)        (_) \n" ;


string frame18 = "  ___    ___       ___ \n |__ \\  |__ \\     |__ \\\n   / /    / /       / /\n  |_|    |_|       |_| \n  (_)    (_)       (_) \n" ;


string frame19 = "  ___    ___      ___ \n |__ \\  |__ \\    |__ \\\n   / /    / /      / /\n  |_|    |_|      |_| \n  (_)    (_)      (_) \n" ;


string frame20 = "  ___    ___     ___ \n |__ \\  |__ \\   |__ \\\n   / /    / /     / /\n  |_|    |_|     |_| \n  (_)    (_)     (_) \n" ;


string frame21 = "  ___    ___    ___ \n |__ \\  |__ \\  |__ \\\n   / /    / /    / /\n  |_|    |_|    |_| \n  (_)    (_)    (_) \n" ;


string frame22 = "  ___    ___    ___             ___ \n |__ \\  |__ \\  |__ \\           |__ \\\n   / /    / /    / /             / /\n  |_|    |_|    |_|             |_| \n  (_)    (_)    (_)             (_) \n" ;


string frame23 = "  ___    ___    ___            ___ \n |__ \\  |__ \\  |__ \\          |__ \\\n   / /    / /    / /            / /\n  |_|    |_|    |_|            |_| \n  (_)    (_)    (_)            (_) \n" ;


string frame24 = "  ___    ___    ___           ___ \n |__ \\  |__ \\  |__ \\         |__ \\\n   / /    / /    / /           / /\n  |_|    |_|    |_|           |_| \n  (_)    (_)    (_)           (_) \n" ;


string frame25 = "  ___    ___    ___          ___ \n |__ \\  |__ \\  |__ \\        |__ \\\n   / /    / /    / /          / /\n  |_|    |_|    |_|          |_| \n  (_)    (_)    (_)          (_) \n" ;


string frame26 = "  ___    ___    ___         ___ \n |__ \\  |__ \\  |__ \\       |__ \\\n   / /    / /    / /         / /\n  |_|    |_|    |_|         |_| \n  (_)    (_)    (_)         (_) \n" ;


string frame27 = "  ___    ___    ___        ___ \n |__ \\  |__ \\  |__ \\      |__ \\\n   / /    / /    / /        / /\n  |_|    |_|    |_|        |_| \n  (_)    (_)    (_)        (_) \n" ;


string frame28 = "  ___    ___    ___       ___ \n |__ \\  |__ \\  |__ \\     |__ \\\n   / /    / /    / /       / /\n  |_|    |_|    |_|       |_| \n  (_)    (_)    (_)       (_) \n" ;


string frame29 = "  ___    ___    ___      ___ \n |__ \\  |__ \\  |__ \\    |__ \\\n   / /    / /    / /      / /\n  |_|    |_|    |_|      |_| \n  (_)    (_)    (_)      (_) \n" ;


string frame30 = "  ___    ___    ___     ___ \n |__ \\  |__ \\  |__ \\   |__ \\\n   / /    / /    / /     / /\n  |_|    |_|    |_|     |_| \n  (_)    (_)    (_)     (_) \n" ;


string frame31 = "  ___    ___    ___    ___ \n |__ \\  |__ \\  |__ \\  |__ \\\n   / /    / /    / /    / /\n  |_|    |_|    |_|    |_| \n  (_)    (_)    (_)    (_) \n" ;


string frame32 = "  ___            ___  ___      ___  ____   _______ _____ _____________   __\n / _ \\    ___    |  \\/  |      |  \\/  \\ \\ / /  ___|_   _|  ___| ___ \\ \\ / /\n/ /_\\ \\  ( _ )   | .  . |      | .  . |\\ V /\\ `--.  | | | |__ | |_/ /\\ V / \n|  _  |  / _ \\/\  | |\\/| |      | |\\/| | \\ /  `--. \\ | | |  __||    /  \\ /  \n| | | | | (_>  < | |  | |      | |  | | | | /\\__/ / | | | |___| |\\ \\  | |  \n\\_| |_/  \\___/\\/ \\_|  |_/      \\_|  |_/ \\_/ \\____/  \\_/ \\____/\\_| \\_| \\_/  \n" ;

cout << "\e[H\e[2J";
cout << frame1;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame2;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame3;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame4;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame5;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame6;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame7;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame8;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame9;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame10;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame11;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame12;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame13;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame14;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame15;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame16;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame17;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame18;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame19;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame20;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame21;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame22;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame23;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame24;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame25;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame26;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame27;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame28;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame29;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame30;
this_thread::sleep_for(chrono::milliseconds(80));
cout << "\e[H\e[2J";
cout << frame31 << endl;
cout << frame32 << endl;


return 0;
}
