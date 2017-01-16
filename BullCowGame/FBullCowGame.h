/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind
*/


#pragma once

#include <string>

// to make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	//Numbers,
	//Empty_Input,
	//Already_Used,
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord();
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;


	//int32 TriesLeft();

	void Reset(); // TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString); // counts bulls & cows, and increases turn number. assuming valid guess



// Please try and ignore this and focus on the interface above
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};