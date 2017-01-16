/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsibel for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		BCGame.GetHiddenWord();
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain == true);
	
	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls & Cows, a fun word game!\n";
	std::cout << std::endl << "    ,           ,          ";
	std::cout << std::endl << "   /             \\                    ,/         \\,";
	std::cout << std::endl << "  ((__-^^-,-^^-__))                  ((__,-'''-,__))";
	std::cout << std::endl << "    `-_---' `---_-'                   `--)~   ~(--`";
	std::cout << std::endl << "    <__|o` 'o|__>                    .-'(       )`-,";
	std::cout << std::endl << "       \\  `  /                       `~~`d\\   /b`~~`";
	std::cout << std::endl << "        ): :(                            |     |";
	std::cout << std::endl << "        :o_o:                            (6___6)";
	std::cout << std::endl << "        ''-''                             `---`" << std::endl << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << "You need to guess the Word in " << BCGame.GetMaxTries() << " tries\n";
	std::cout << "After every guess the number of 'Bulls' and 'Cows' will be output to you.\n";
	std::cout << "Bulls are correct letters in the correct place, whereas Cows are correct letters in the wrong place.\n\n";

	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		// get a guess from the player and print it back
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << "| Enter your guess: ";
		std::getline(std::cin, Guess); // TODO fix bug where this line is skipped in the first run 

		// check guess validity and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only use lowercase letters.\n";
			break;
		default: // assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Yes / No) ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << "\n\n";

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
