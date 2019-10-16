#include <iostream>
#include <ctime> 
#include <random>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

int bottles;
int playerHP;
int dragonHP;
int lastDragonHP;
int bottlesAsked;

void talkToDragon() {
	sleep_for(2s);
	cout << "~Dragon: Well done fighter, this was a great battle. I will reward you for your bravery!\n";
	sleep_for(1s);
	cout << "~Dragon: Here is another bottle of potion. Use it as you please.\n";
	bottles++;
	sleep_for(1s);
	cout << "\nYou now have " << bottles << " bottles.\n";
}

void useBottles() {
	char response;
	if(bottles > 0) {
		cout << "Would you like to use a bottle of potion?(Y/N)\n";
		cout << "Your HP is " << playerHP << endl;
		cin >> response;

		if(response == 'Y') {
			bottles--;
			playerHP += 50;
			cout << "Your health is at " << playerHP << endl;
			cout << "* happy knight noises *\n";
			sleep_for(2s);
			useBottles();
		}
		
	} else {
		cout << "Too bad you have no bottles left to restore your health.\n";
	}

}

void advance() {
	dragonHP = lastDragonHP + 50;
	lastDragonHP = dragonHP;
	bottlesAsked = bottlesAsked + 1;

	sleep_for(1s);
	cout << "* continuing journey *\n\n";
	sleep_for(3s);
}

int fightOutcome() {
	if(playerHP <= 0) {
		cout << "\nYou lost the battle. Game over!\n";
		return 0;
	} else {
		cout << "\nYou have " << playerHP << " HP left.\n";
	}

	if(dragonHP <= 0) {
		cout << "\nYou killed the Dragon.\nWell done, fighter! You shall continue your journey.\n";
		return 1;
	} else {
		cout << "\nYou did not kill the Dragon.\n\n";
		return 2;
	}
}

void fightDragon() {
	int dealtDamage;

	for(int i = 0; i < 3; i++) {
		sleep_for(3s);

		srand(time(NULL));
		dealtDamage = rand() % 41 + 1;
		cout << "You dealt " << dealtDamage << " damage to the Dragon.\n";
		dragonHP -= dealtDamage;

		if(dragonHP > 0) {
			cout << "Dragon HP: " << dragonHP << endl;
		} else {
			break;
		}

		sleep_for(3s);

		srand(time(NULL));
		dealtDamage = rand() % 41 + 1;
		cout << "The Dragon dealt " << dealtDamage << " damage to you.\n";
		playerHP -= dealtDamage;
		
		if(playerHP > 0) {
			cout << "Your HP:" << playerHP << endl;
		} else {
			break;
		}

	}
}

// char choice() {
// 	char answer;

// 	cin >> answer;

// 	switch(answer) {
// 		case 'F':
// 			fightDragon();
// 			break;
// 		case 'G':
// 			cout << "\nYou gave the Dragon " << bottlesAsked <<  " bottles, were you not brave enough to fight it?\n";
// 			bottles -= bottlesAsked;
// 			break;
// 		case 'R':
// 			throw runtime_error("Game over!\n");
// 		default:
// 			cout << "Error: wrong input, try again!\n";
// 			choice();
// 			break;
// 	}
// }

void discussion() {
	sleep_for(2s);
	cout << "~Dragon: If you want to pass you need to give me " << bottlesAsked << " bottles.\n\n";

	if(bottles >= bottlesAsked) {
		cout << "You have " << bottles << " bottles, will you give them to the Dragon (press G) or will you fight it (press F)?\n";
	} else {
		cout << "You don't have enough bottles, will you run (press R) or will you fight the Dragon (press F)?\n";
	}

}

int game() {
	while(playerHP > 0) {
		discussion();
		char answer;

		cin >> answer;
		switch(answer) {
			case 'G':
				cout << "\nYou gave the Dragon " << bottlesAsked <<  " bottles, were you not brave enough to fight it?\n";
				bottles -= bottlesAsked;
				break;
			
			case 'R':
				throw runtime_error("Game over!\n");
			
			default:
				fightDragon();
				switch (fightOutcome()) {
					case 0:
						return 0;
						break;
					case 2:
						talkToDragon();
						cout << "It seems that the fighting a dragon is not so easy.\n";
						useBottles();
						break;
				}
		}
		advance();
	}
	return 1;
}

int main() {
	playerHP = 100;
	dragonHP = 100;
	lastDragonHP = dragonHP;
	bottlesAsked = 3;
	char answer;

	srand(time(NULL));
	bottles = rand() % 4;

	cout << "You have " << bottles << " bottles of potion, use them carefully.\n\n";

	try {
		if(game() == 0)
			return 0;
	} catch (runtime_error& e) {
		cout << e.what();
		return 1;
	}

	return 0;
}
