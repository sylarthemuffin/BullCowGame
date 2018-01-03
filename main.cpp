/*
	This is the console executable that makes use of the BullCow class.
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic, see the FBullCowGame class.
	Author: ztk
*/
#include "stdafx.h"
#include "FBullCowgame.h"
#include <string>
#include <iostream>

using FText = std::string;
using int32 = int;

void printIntroduction();
void printGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; //create a new game instance

int main() {

	bool WantsToPlayAgain = true;
	do {
		printIntroduction();
		BCGame.Reset();
		PlayGame();
		WantsToPlayAgain = AskToPlayAgain();
	} while (WantsToPlayAgain);
	
	return 0;
}

//prints the introductory instructions for the game
void printIntroduction() {
	std::cout << "Welcome to Bulls and Cows, a word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void printGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE! YOU'VE WON!\n";
	}
	else if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
		std::cout << "Better luck next time.\n";
	}
	return;
}



void PlayGame() {
	int32 MaxTries = BCGame.GetMaxTries();
	//loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}
	//summarize game
	printGameSummary();
	
	return;
}

//loop continually until the user gives a valid guess
FText GetValidGuess() { 
	EGuessStatus Status = EGuessStatus::Invalid_status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ": ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {

		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n"; 
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (a word with no repeating letters).\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only use lowercase letters.\n";
			break;

		default:
			//assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get valid input
	
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText resp = "";
	std::getline(std::cin, resp);
	std::cout << std::endl;
	if (resp[0] == 'y' || resp[0] == 'Y') {
		return true;
	}
	else if (resp[0] == 'n' || resp[0] == 'N') {
		return false;
	}
	else {
		return AskToPlayAgain();
	}
}