#pragma once
#include <string>
#include <map>
#define TMap std::map

enum class EWordStatus {         
	OK,Not_Isogram,Empty_String,Wrong_Length,Invalid_Input	// Using enum with class so that we can use OK in other enums too.
};

using FString = std::string;
using int32 = int;
 

struct BullCowCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	FString GetHiddenWord() const;
	int32 GetMaxTries() const; // With const this member function won't let modify the data types inside it
	int32 GetCurrentTry() const; 
	int32 GetHiddenWordLength() const;
	bool IsGameWon();
	EWordStatus CheckGuessValidity(FString) const; //TODO Checking validity of guess
	
	void SetHiddenWord(FString word); // Set the Hidden Word
	void Reset(); 
	BullCowCount SubmitGuess(FString);
	

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};