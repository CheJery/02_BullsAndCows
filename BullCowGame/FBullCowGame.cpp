#pragma once

#include "FBullCowGame.h"
#include <map>
#include <iostream>

// to make syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() //default constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}
int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}
bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32,int32> WordLengthToMaxTries
	{
		{2,3},
		{3,4},
		{4,8},
		{5,11},
		{6,16},
		{7,20},
		{8,30},
		{9,40},
		{10,50},
		{15,100}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "oberhand";
	//MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the geuss isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, increments turn, and teturns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) // if they're in the same place
				{
					BullCowCount.Bulls++; // increment bulls
				}
				else
				{
					BullCowCount.Cows++; // must bew cow (increment cows)
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 or 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap <char, bool> LetterSeen; // creat map
	for (auto Letter : Word) // loop for all the letters of the word
	{
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter]) // if the letter is already mapped
		{
			return false; // set value of IsIsogram to false
		}
		else // if the letter isn't mapped yet
		{
			LetterSeen[Letter] = true; // add the letter to the map
		}


	}

	return true; // for example in the case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	//treat \0 and spaces

	for (auto Letter : Word) // loop for all the letters of the word
	{
		if (!islower(Letter)) // if the letter is not lowercase
		{
			return false;  //set value of IsLowercase to false
		}
	}
	return true;
}

FString FBullCowGame::GetHiddenWord()
{
	TMap <int32, FString> ChooseHiddenWord
	{
		{ 2,"du" },
		{ 3,"sie" },
		{ 4,"nase" },
		{ 5,"tisch" },
		{ 6,"tablet" },
		{ 7,"sektion" },
		{ 8,"oberhand" },
		{ 9,"bahngleis" },
		{ 10,"cornflakes" },
		{ 15,"bildungsprojekt" }
	}; // all these words must be isograms for the game to work
	int32 ChosenLength = 0;

	// TODO move to main as it's view code and not supposed to be here
	system("cls");
	std::cout << "How long do you want your isogram to be (2-10, 15)?\n";
	std::cin >> ChosenLength;

	MyHiddenWord = ChooseHiddenWord[ChosenLength];
	


	return MyHiddenWord;
}