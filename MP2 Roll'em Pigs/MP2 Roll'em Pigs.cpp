// MP2 Roll Pigs.cpp - Breanna Sproul - 19 October 2023
// This program simulates the game of Pig.
// Pig is a 2 player game that uses dice rolling as a way to accumulate and lose points.
// 1st to 100 points win. Player can store points or roll again. Die face of 1 causes point loss and turn change.
//This version includes a human player and a COM player.

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

//function prototypes
char getPlayerInput(void);
bool hasWinningScore(int score);
bool isTurnPointsLost(int die1value, int die2value);
bool isGameScoreLost(int die1value, int die2value);
int rollDie(void);

int main() {
	//variables
	int score = 0;
	bool win_reached = false;
	int die1value;
	int die2value;
	int player_turn_score = 0;
	int player_turn_total = 0;
	int player_game_score = 0;
	int players_turn = true;
	int COM_turn_score = 0;
	int COM_turn_total = 0;
	int COM_game_score = 0;
	srand(time(0));

	cout << "This is the game of Rolling Pigs. ";
	cout << "Each player rolls 2 dice and adds their values together, ";
	cout << "then the player decides if they want to store their points or continue rolling. ";
	cout << "If a 1 is rolled, all turn points are lost. If both dice are 1, then all game points are lost. ";
	cout << "The first player to 100 game points wins." << endl;

	while (true) {
		//players turn
		while (players_turn == true && win_reached == false) {
			//roll the die
			die1value = rollDie();
			die2value = rollDie();
			cout << "You rolled a " << die1value << " and a " << die2value << endl;

			//snake eye check
			if (isGameScoreLost(die1value, die2value) == true) {
				cout << "You rolled snake eyes! Both your turn points and game points are lost, and your turn ends" << endl;
				player_game_score = 0;
				player_turn_score = 0;
				player_turn_total = 0;
				players_turn = false;
				cout << endl;
				break;
			}
			// 1 die check
			else if (isTurnPointsLost(die1value, die2value) == true) {
				cout << "You rolled a 1! Your turn points are lost, and your turn ends" << endl;
				player_turn_score = 0;
				players_turn = false;
				player_turn_total = 0;
				cout << endl;
				break;
			}
			//player input check
			else {
				player_turn_score = die1value + die2value;
				cout << "Your turn points are: " << player_turn_score << endl;
				player_turn_total += player_turn_score;
				player_turn_score = 0;
				if (getPlayerInput() == 'e') {
					player_game_score = player_game_score + player_turn_total;
					cout << "Your game score is: " << player_game_score << endl;
					player_turn_total = 0;
					cout << endl;
					if (player_game_score >= 100) {
						score = player_game_score;
						win_reached = true;
						break;
					}
					//switch turn
					players_turn = false;
					break;
				}

			}

		}
		//COM turn
		while (players_turn == false && win_reached == false) {
			//roll the die
			die1value = rollDie();
			die2value = rollDie();
			cout << "COM rolled a " << die1value << " and a " << die2value << endl;

			//snake eye check
			if (isGameScoreLost(die1value, die2value) == true) {
				cout << "COM rolled snake eyes! Both COM's turn points and game points are lost, and COM's turn ends" << endl;
				COM_game_score = 0;
				COM_turn_score = 0;
				COM_turn_total = 0;
				players_turn = true;
				cout << endl;
				break;
			}
			// 1 die check
			else if (isTurnPointsLost(die1value, die2value) == true) {
				cout << "COM rolled a 1! COM's turn points are lost, and COM's turn ends" << endl;
				COM_turn_score = 0;
				COM_turn_total = 0;
				players_turn = true;
				cout << endl;
				break;
			}
			//COM input check
			else {
				COM_turn_score = die1value + die2value;
				cout << "COM's turn points are: " << COM_turn_score << endl;
				COM_turn_total += COM_turn_score;
				COM_turn_score = 0;
				if (COM_turn_total >= 23) {
					COM_game_score = COM_game_score + COM_turn_total;
					cout << "COM game score is: " << COM_game_score << endl;
					COM_turn_total = 0;
					cout << endl;
					if (COM_game_score >= 100) {
						score = COM_game_score;
						win_reached = true;
						break;
					}
					//switch turn
					players_turn = true;
					break;
				}

			}


		}
		

		//outputs the win and terminates program
		if (hasWinningScore(score) == true) {
			cout << "A score of 100 points has been reached! Thank you for playing!" << endl;
			break;
		}
	}
}

//function definitions

//getPlayerInput: gets input from the user to determine if turn continues or ends
//@param: uses void to allow any input
//@return: 'r' or 'e'
char getPlayerInput(void) {
	cout << "To roll again press r, or to store your points and end the turn press e: ";
	char input;
	cin >> input;

	if (input == 'r' || input == 'R') {
		return 'r';
	}
	else if (input == 'e' || input == 'E') {
		return 'e';
	}
	else {
		cout << "Sorry but that input was not one of the suggestions given.";
		getPlayerInput();
		//idk if this^ will work or not
	}
}

//hasWinningScore: tells the program if the win score was reached
//@param: determines boolean from int score
//@return: returns either true or false based on the die values
bool hasWinningScore(int score) {
	if (score >= 100) {
		return true;
	}
	else { return false; }
}

//isTurnPointsLost: tells the program if the turn score is lost
//@param: determines boolean from int die1value and int die2vlaue
//@return: returns either true or false based on the die values
bool isTurnPointsLost(int die1value, int die2value) {
	if (die1value == 1 && die2value != 1) {
		return true;
	}
	else if (die1value != 1 && die2value == 1) {
		return true;
	}
	else { return false; }
}

//isGameScoreLost: tells the program if the game score is lost
//@param: determines boolean from int die1value and int die2vlaue
//@return: returns either true or false based on the die values
bool isGameScoreLost(int die1value, int die2value) {
	if (die1value == 1 && die2value == 1) {
		return true;
	}
	else { return false; }
}

//rollDie: rolls a 6 sided die
//@param: void
//@return: int value of 1-6 of the die
int rollDie(void) {
	const int NUMBER_OF_DIE_SIDES = 6;
	const int LOWEST_DIE_VALUE = 1;

	return rand() % NUMBER_OF_DIE_SIDES + LOWEST_DIE_VALUE;
}