// GameLoop.cpp : Handles the dice game.
//
// Winston To
// 2/20/21
// IT 312
// 7-1 Final Project Submission: Dice Game
//
/* LCR Game, runs  */

#include "GameLoop.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>;

using namespace std;

//display game rules
void Game::DisplayGameRules()
{
	string myText;
	ifstream GameRules("6-3Winston.txt");
	while (getline(GameRules, myText)) {
		cout << myText << endl;
	}
	GameRules.close();
}

//validate that player chooses 3 or more players
void Game::ValidateInput(int a)
{
	while (a < 3) {
		cout << "The game requires a minimum of 3 players"
			<< endl
			<< "How many players will be playing? ";
		cin >> a;
	}

	SetNumberOfPlayers(a); //assigns int value to game class variable for later player object array declaration.
}

//ask player for how many players in game
void Game::GameSetup()
{
	int input;

	cout << "How many players will be playing? (req. minimum of 3) ";
	cin >> input;
	ValidateInput(input);


}

//roll dice mechanic, takes current player object as parameter
int Game::RollDice(Player& p)
{
	//variables
	int pChips = p.PlayerChips();
	int dices[3] = {};
	string output[3] = {};

	//loop that randomizes 3 rolls & assigns the appropriate outcomes to object's variable and output variable
	for (int i = 0; i <= 2; i++) {
		dices[i] = (1 + (rand() % 6));

		if (dices[i] == 1)
		{
			p.SetResults(i, 'L');
			output[i] = " and passes one chip to left player.";
		}
		else if (dices[i] == 2)
		{
			p.SetResults(i, 'R');
			output[i] = " and passes one chip to the right player.";
		}
		else if (dices[i] == 3)
		{
			p.SetResults(i, 'C');
			output[i] = " and places one chip into the pot.";
		}
		else if (dices[i] > 3 && dices[i] < 7)
		{
			p.SetResults(i, '*');
			output[i] = " and takes no action.";
		}
	}

	//only output results to number of appropriate rolls. if player object has 1 chip, 1 roll, 2 chip, 2 roll, 3+ chips, 3 rolls
	if (pChips == 1)
	{
		cout << endl << "DICE 1: " << p.GetResults(0) << output[0] << endl << endl;
		return 1;
	}
	else if (pChips == 2)
	{
		cout << endl << "DICE 1: " << p.GetResults(0) << output[0] << endl;
		cout << "DICE 2: " << p.GetResults(1) << output[1] << endl << endl;
		return 2;
	}
	else if (pChips >= 3)
	{
		cout << endl << "DICE 1: " << p.GetResults(0) << output[0] << endl;
		cout << "DICE 2: " << p.GetResults(1) << output[1] << endl;
		cout << "DICE 3: " << p.GetResults(2) << output[2] << endl << endl;
		return 3;
	}
}

//main game method
void Game::RunGame()
{
	//check if player is reedy to start
	char input;
	cout << endl << "Would you like to start playing? (y/n) ";
	cin >> input;
	cout << endl;

	if (input == 'y') {
		cout << "Starting Game!" << endl << endl;

		GameSetup();

		//create player objects arrray
		Player* gPlayer = new Player[GetPlayers()];
		int roundLength = GetPlayers() - 1; //loop prime for round cycle

		bool gameInPlay = true; //round loop primer
		while (gameInPlay) {

			//formatted output
			cout << endl << "___________________________________________________________"
				<< endl << endl << "Round " << Round() << "!"
				<< endl << "___________________________________________________________"
				<< endl;

			//player turn cycle loop
			for (int i = 0; i <= roundLength; i++)
			{
				//display corresponding player's turn
				cout << endl << "Player " << i + 1 << "'s turn" << endl;

				//only allow player to roll if they have chips
				if (gPlayer[i].HasChips())
				{
					cout << "Player " << i + 1 << " has " << gPlayer[i].PlayerChips() << " chip(s). Press 'r' to roll: ";
					char rollInput;
					cin >> rollInput;
					while (rollInput != 'r') {
						cout << "press 'r' to roll: ";
						cin >> rollInput;
					}

					//roll dice
					int rolls = RollDice(gPlayer[i]);

					//resolve roll results
					for (int y = 0; y <= (rolls - 1); y++) {
						if (gPlayer[i].GetResults(y) == 'L') {
							gPlayer[i].SubChip();
							//check to see if pointer is in range, if it is player 1 passing chip to the left, it goes to the last player(indexed at roundLength)
							if (i == 0) {
								gPlayer[roundLength].AddChip();
								if (gPlayer[roundLength].HasChips() == false) {
									gPlayer[roundLength].SetHasChips(true);
								}
							}
							else
							{
								gPlayer[(i - 1)].AddChip();
								if (gPlayer[(i - 1)].HasChips() == false) {
									gPlayer[(i - 1)].SetHasChips(true);
								}
							}
						}
						else if (gPlayer[i].GetResults(y) == 'R') {
							gPlayer[i].SubChip();
							//check to see if pointer is in range, if it is the last player passing chip to the right, it goees to the first player(indexed at 0)
							if (i == roundLength) {
								gPlayer[0].AddChip();
							}
							else
							{
								gPlayer[(i + 1)].AddChip();
							}
						}
						else if (gPlayer[i].GetResults(y) == 'C') {
							gPlayer[i].SubChip();
							IncPot();
						}
						gPlayer[i].SetResults(y, '0'); //reset results for player object at end of turn
					}
				}
				//skip turrn if player does not have chips
				else if (!(gPlayer[i].HasChips()))
				{
					cout << "Player " << i + 1 << " has no chips!" << endl << "They skip their turn this round!";
				}
			}

			//check for winner
			int hasChipCount = 0;
			int z = 0;
			for (int x = 0; x <= roundLength; x++) {
				if (gPlayer[x].HasChips()) {
					hasChipCount += 1;
					z = x;
				}
			}
			if (hasChipCount == 1) {
				gameInPlay = false;
				cout << endl << "___________________________________________________________" << endl << endl;
				cout << "Player " << z << " has won the game!" << endl
					<< "The game went on for " << Round() << " rounds!" << endl
					<< "Player " << z << " ended the game with " << gPlayer[z].PlayerChips() << " chips!" << endl
					<< GetPot() << " chips were placed in the pot" << endl;
				cout << "___________________________________________________________";
			}

			EndRound();
		}

	}
	else {
		cout << "Exiting game." << endl;
	}
}