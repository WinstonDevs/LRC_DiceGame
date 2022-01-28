// GameLoop.h : Game class
//
// Winston To
// 2/20/21
// IT 312
// 7-1 Final Project Submission: Dice Game
//
/* LCR Game, runs  */

#pragma once
#include<string>
#include "Player.h"

class Game
{
private:
	//game variables
	int numberOfPlayers = 0;
	int rounds = 1;
	int potCount = 0;

	//internal game methods
	int RollDice(Player& p);
	void GameSetup();
	void ValidateInput(int a);

public:
	//external game methods
	void DisplayGameRules();
	void RunGame();

	//set number of players
	void SetNumberOfPlayers(int b)
	{
		numberOfPlayers = b;
	}

	//get number of players
	int GetPlayers()
	{
		return numberOfPlayers;
	}

	//increase round count
	void EndRound()
	{
		rounds += 1;
	}

	//get round count
	int Round()
	{
		return rounds;
	}

	//increase pot count
	void IncPot()
	{
		potCount += 1;
	}

	//get round count
	int GetPot()
	{
		return potCount;
	}
};