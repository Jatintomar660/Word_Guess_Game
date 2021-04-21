#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

FBullCowGame BCGame;

FString Words10[64];
FString Words9[64];
FString Words8[64];
FString Words7[64];
FString Words6[64];
FString Words5[64];
FString Words4[64];
FString Words3[64];

void PrintIntro();
void CheckGameStatus(EWordStatus,Ftext);
void PrintGameSummary();
int32 GetDifficulty();
Ftext SetString(int32 n);
void PlayGame();
Ftext GetInput();
bool AskToPlayAgain();
void TakeOutWords(FString path,FString Words[]);
void PreProcess();

int main()
{	
	srand(time(0));
	PreProcess();
	
	// 0 Bull and 0 Cow Don't Increase Current Try 

	bool AskToPlay=false;
	do{
		PrintIntro();
		PlayGame();
		AskToPlay=AskToPlayAgain();
		std::cout << "\n";
	} while (AskToPlay);
	
	return 0;

}


void PrintIntro()
{
	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	// Introduce the game
	std::cout << "Welcome To the Bull Cow Game, A Fun Word Game" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |----- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you think of the isogram I'm thinking of?\n" << std::endl;
	return;
}

void CheckGameStatus(EWordStatus Status, Ftext Guess)
{
	switch (Status)
	{
	case EWordStatus::Empty_String:
		std::cout << "Please Enter Something!\n";
		break;

	case EWordStatus::Wrong_Length:
		std::cout << "Please Enter " << BCGame.GetHiddenWordLength() << " letter word\n";
		break;

	case EWordStatus::Not_Isogram:
		std::cout << "Please Enter word with no repeatating letters (Isogram)\n";
		break;

	case EWordStatus::Invalid_Input:
		std::cout << "Please Enter Word in lowercase\n";
		break;

	default:
		BullCowCount Count = BCGame.SubmitGuess(Guess);
		std::cout << "Bulls :" << Count.Bull;
		std::cout << "\t Cows :" << Count.Cow << std::endl;
	}
}

Ftext GetInput()
{
	// Take the guess
	std::cout <<"Try "<< BCGame.GetCurrentTry()<<" of "<<BCGame.GetMaxTries() <<" Enter your Guess: ";
	Ftext Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	Ftext Response ;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {std::cout << "\nYou Won -- Thanks for playing!!\n\n";}
	else
	{
		std::cout << "\nThe Word Was : " << BCGame.GetHiddenWord() << "\n";
		std::cout << "\nBetter Luck Next Time \n\n";
	}
}

int32 GetDifficulty()
{
	int32 n;
	std::cout << "Enter The Word Length you want to guess from 3 to 10: ";
	std::cin >> n;
	std::cin.ignore();
	return n;
}

Ftext SetString(int32 n)
{
	int32 j = rand() % 64;
	if (n == 3){return Words3[j];}
	else if (n == 4) { return Words4[j]; }
	else if (n == 5) { return Words5[j]; }
	else if (n == 6) { return Words6[j]; }
	else if (n == 7) { return Words7[j]; }
	else if (n == 8) { return Words8[j]; }
	else if (n == 9) { return Words9[j]; }
	else  { return Words10[j]; }
}

void PlayGame()
{
	int WLen = GetDifficulty();
	Ftext HWord = SetString(WLen);
	BCGame.SetHiddenWord(HWord);
	int32 NUMBER_OF_TURNS = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=NUMBER_OF_TURNS )
	{
		Ftext Guess=GetInput();	
		EWordStatus Status = BCGame.CheckGuessValidity(Guess);
		CheckGameStatus(Status, Guess);
	}
	// Game Summary
	PrintGameSummary();
	//Reseting The Game
	BCGame.Reset();
	
	return;
}

void TakeOutWords(FString path,FString Words[])
{
	FString line;
	std::ifstream fin;
	fin.open(path);
	int i = 0;
	int j = rand() % 30;
	int c = 0;
	while (fin && i<64) {
		std::getline(fin, line);
		/*std::cout << line << "\n";*/
		if(c>=j)
		{
			Words[i] = line;
			i++;
		}
		c++;
	}
	fin.close();
}

void PreProcess()
{
	TakeOutWords("Data/10Letter.txt", Words10);
	TakeOutWords("Data/9Letter.txt", Words9);
	TakeOutWords("Data/8Letter.txt", Words8);
	TakeOutWords("Data/7Letter.txt", Words7);
	TakeOutWords("Data/6Letter.txt", Words6);
	TakeOutWords("Data/5Letter.txt", Words5);
	TakeOutWords("Data/4Letter.txt", Words4);
	TakeOutWords("Data/3Letter.txt", Words3);
}

