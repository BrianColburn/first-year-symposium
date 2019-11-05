#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
int main ()
{

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
    this_thread::sleep_for(chrono::milliseconds(80));
  }
return 0;
}