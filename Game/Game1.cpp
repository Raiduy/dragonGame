#include <iostream>
#include <ctime> 
#include <random>

using namespace std;

void fightDragon(int& bottles, int& playerHP, int& dragonHP) {
	for(int i = 0; i < 3; i++) {
		if(dragonHP > 0) {
			srand(time(NULL));
			dragonHP -= rand() % 41 + 1;
		} else {
			break;
		
}
		if(playerHP > 0) {				
			srand(time(NULL));
			playerHP -= rand() % 41 + 1;
		} else {
			break;
		}
	}
}

void firstChoice(int& bottles, int& playerHP, int& dragonHP) {
	char answer;

	cin >> answer;

	switch(answer) {
		case 'F':
			fightDragon(bottles, playerHP, dragonHP);
			break;
		case 'G':
			//continueGoing();
			break;
		case 'R':
			throw runtime_error("Game over!\n");
		default:
			cout << "Error: wrong input, try again!\n";
			firstChoice(bottles, playerHP, dragonHP);
			break;
	}
}

void firstDiscussion(int numberOfBottles) {
	// first discussion
	cout << "Dragon: If you want to pass you need to give me 3 bottles.\n";

	if(numberOfBottles == 3) {
		cout << "You have 3 bottles, will you give them to the Dragon (press G) or will you fight it (press F)?\n";
	} else {
		cout << "You don't have 3 bottles, will you run (press R) or will you fight the Dragon (press F)?\n";
	}

}

int main() {
	int playerHP = 100, dragonHP = 100, bottles;
	char answer;

	srand(time(NULL));
	bottles = rand() % 4;

	cout << "You have " << bottles << " bottles of potion, use them carefully.\n";

	firstDiscussion(bottles);

	try {
		firstChoice(bottles, playerHP, dragonHP);
	} catch (runtime_error& e) {
		cout << e.what();
	}

	if(playerHP < 0) {
		cout << "You lost the battle. Game over!\n";
		return 0;
	} else {
		cout << "You have " << playerHP << " HP.\n";
	}

	if(dragonHP < 0) {
		cout << "You killed the Dragon.\n";
		//continueGoing();
	} else {
		cout << "You did not kill the Dragon\n";
		//secondTalk();
	}

	return 0;
}
