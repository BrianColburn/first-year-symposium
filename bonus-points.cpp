#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
#define move_up(rows) std::cout << "\e[" #rows "A"
#define move_down(rows) std::cout << "\e[" #rows "B"
#include "getch.h"

int main() {
	//getch();
	//getch();
	//int c = getch();
	//cout << c << endl;
	int i = 0;
	
	cout << "\e[H┌──────────┐\n"
		 << "│          │\n"
		 << "└──────────┘\n";
	while (true) {
		move_up(3);
		cout << "\e[H┌──────────\e[G\e[" << (i%10 + 1) << "C┬\e[3B\e[G";
		cout << "\e[2A\e[1C"
			 << (i&1?"\e[0;36m":"\e[0;92m") 
			 << "MicrosOOFt"
			 << "\e[0;m\n└──────────\e[G\e[" << (i%10 + 1) << "C┴\n";
		//i++;
		//this_thread::sleep_for(chrono::milliseconds(500));
		getch();
		getch();
		i += (getch()) == 68 ? -1 : 1;
	}
	return 0;
}
