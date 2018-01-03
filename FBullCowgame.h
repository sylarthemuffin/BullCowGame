#pragma once
//Author: ztk
#include <string>

using FString = std::string;
using int32 = int; 

//all values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{

	Invalid_status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_length
};


class FBullCowGame {

public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;

	void Reset(); //TODO: make a new reset value
	FBullCowCount SubmitValidGuess(FString);

//Ignore private variables, focus on the public interface^^
private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	bool isIsogram() const;
	FString MyHiddenWord;
	bool bIsGameWon;
};