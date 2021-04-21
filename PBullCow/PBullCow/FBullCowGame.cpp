#include "FBullCowGame.h"


FBullCowGame::FBullCowGame()
{
    Reset();
}


void FBullCowGame::SetHiddenWord(FString word)
{
    MyHiddenWord = word;
    return;
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyCurrentTry = 1;
    MyHiddenWord = HIDDEN_WORD;
    bIsGameWon = false;
    return;
}

bool FBullCowGame::IsGameWon(){ return bIsGameWon;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

FString FBullCowGame::GetHiddenWord() const
{
    return MyHiddenWord;
}

int32 FBullCowGame::GetMaxTries () const
{
    TMap <int32, int32> WordLenToMaxTry{ {3,6},{4,8},{5,9},{6,11},{7,15},{8,18},{9,20},{10,22}};
    return WordLenToMaxTry[MyHiddenWord.length()];
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    // Empty String
    if (Guess.length() < 1) { return EWordStatus::Empty_String; }

    // Length is incorrect
    if (Guess.length() != GetHiddenWordLength()) { return EWordStatus::Wrong_Length; }

    // Checking Repeats in String
    if (!IsIsogram(Guess)) { return EWordStatus::Not_Isogram; }

    // Checking Lowercase
    if (!IsLowercase(Guess)) { return EWordStatus::Invalid_Input; }
    
    return EWordStatus::OK;
}

int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

BullCowCount FBullCowGame::SubmitGuess(FString Guess)
{

    MyCurrentTry++; 
    BullCowCount BullCow; 

    int32 i = 0;
    while (Guess[i] != '\0')
    {
        int32 j = 0;
        while (MyHiddenWord[j] != '\0')
        {
            if (Guess[i] == MyHiddenWord[j])
            {
                if (i == j) { BullCow.Bull++; }
                else { BullCow.Cow++; }
            }
            j++;
        }
        i++;
    }
    if (BullCow.Bull == 0 && BullCow.Cow == 0) { MyCurrentTry--; }
    if (BullCow.Bull == GetHiddenWordLength()) { bIsGameWon = true; }
    else { bIsGameWon = false; }

    return BullCow;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
    if (Guess.length() <= 1) { return true; }

    TMap <char,bool> LetterSeen;

    for (auto Letter : Guess)
    {
        Letter = tolower(Letter);
       
        if (LetterSeen[Letter]) { return false; }
        else  { LetterSeen[Letter] = true; }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
    int32 i = 0;
    while (Guess[i] != '\0')
    {
        int32 c = Guess[i];
        if (c < 97 || c > 122) { return false; }
        i++;
    }
    return true;
}

