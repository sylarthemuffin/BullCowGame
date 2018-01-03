#include "stdafx.h"
#include "FBullCowgame.h"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() {
	FBullCowGame::Reset();
}

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;  
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "plant";
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const{ return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const{ return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) {// if the guess is not an isogram
		//TODO write function
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase
	else if (false) { //TODO write function 
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_length;
	}
	//otherwise, the guess is good
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

bool FBullCowGame::isIsogram() const {
	return false;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the guess is correct length
	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters with the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				//increment bulls if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
					
				}
				//increment cows if they're not
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;

}