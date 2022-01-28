// Player.h : Player class
//
// Winston To
// 2/20/21
// IT 312
// 7-1 Final Project Submission: Dice Game
//
/* LCR Game, runs  */

#pragma once

#include <iostream>

class Player
{
private:
	//object variables
	int chips = 3;
	bool hasChips = true;
	char results[3] = {};

public:
	Player()
	{
	}

	//Add Chips
	void AddChip()
	{
		//puts player back in play if they recieved a chip and had 0
		if (hasChips == false) {
			hasChips = true;
			std::cout << "The reciever is now back in play!" << std::endl;
		}

		chips += 1;
	}

	//Subtract Chips with checker
	void SubChip()
	{
		chips -= 1;

		//takes player out of play if they ran out of chips
		if (chips <= 0)
		{
			SetHasChips(false);
			std::cout << "The Player has ran out of chips!" << std::endl;
		}
	}

	//chipGetter
	int PlayerChips()
	{
		return chips;
	}

	//hasChips setter
	void SetHasChips(bool z)
	{
		hasChips = z;
	}
	//hasChips getter
	bool HasChips()
	{
		return hasChips;
	}

	//result setter
	void SetResults(int a, char b)
	{
		results[a] = b;
	}
	//result getter
	char GetResults(int a)
	{
		return results[a];
	}
};