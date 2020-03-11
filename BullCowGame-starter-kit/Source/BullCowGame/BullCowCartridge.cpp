// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::SetupGame()
{
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1 )];
    
    Lives = HiddenWord.Len();
    bGameOver = false; // ensure the game over flag is clear

    //Intro Text
    PrintLine(TEXT("Hello, can you to guess the %i letter word?"), HiddenWord.Len()); // Prints a line to the terminal
    PrintLine(TEXT("You have %i attempts to get it right"), Lives);
    PrintLine(TEXT("Press Tab to use the Terminal\nthen type in your Guess, and press enter"));
    PrintLine(TEXT("Good luck!"));

    PrintLine(TEXT("The Hidden Word is: %s "), *HiddenWord); //debug line
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Begin Game
    Super::BeginPlay();
    GetValidWords(Words); // grabs a list of valid words from HiddenWordList.h
    Isograms = GetValidWords(Words);
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    ProcessGuess(PlayerInput);
}

TArray<FString> UBullCowCartridge:: GetValidWords(const TArray<FString>& WordsList) const
{
   TArray<FString> ValidWords;

    for (FString PossibleWord: WordsList)//int32 i = 0; i < WordsList.Num(); i++)
    {
        if (PossibleWord.Len() >= 4 && PossibleWord.Len() <=8 && IsIsogram(PossibleWord)) // checks the length of the strings in Words list and if they're an isogram
        {
            ValidWords.Emplace(PossibleWord); //adds them from Words list array to Valid Words array
        }
        
    }

    return ValidWords; //returns a list (array) of valid words for use
}



void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (bGameOver != true) //if the game is not over
    { 
        ClearScreen(); // clear the terminal

        //check the guess

        //is is the right amount of characters?

        PrintLine(TEXT("You guessed: " + (Guess)));
    
        if (Guess == HiddenWord)
        {
            // success state
            PrintLine(TEXT("Well done, that guess was correct!"));
            PrintLine(TEXT("You Win!"));
            bGameOver = true; // set the game over flag
            PrintLine (TEXT("\nPress Enter to Play again"));

        }

        else if (Guess != HiddenWord)
        {
            FBullCowCount Score = GetBullCows(Guess); //grabs the count of bulls and cows that's returned from GetBullCows

            if (!IsIsogram(Guess))
            {
                PrintLine(TEXT("%i correct letters are in the right position.\nand %i correct letters are in the wrong position"), Score.Bulls, Score.Cows);
                PrintLine(TEXT("But no repeating letters, try again!"));
                return;
            }

            PrintLine(TEXT("%i are correct and in the right place.\n%i are correct and in the wrong position"), Score.Bulls, Score.Cows);
            PrintLine(TEXT("\n\nRemember, the word is %i letters long\nYou now have %i guesses left"), HiddenWord.Len(), Lives);
            LoseLife(); //remove a life function
        }

        return;
    }

    if (bGameOver)
    {
        ClearScreen(); // clear the terminal
        SetupGame(); // reset the game
        return;
    }

    
}


void UBullCowCartridge::LoseLife()
{
    if (Lives > 0)
    {
        --Lives; //minus a life
        PrintLine (TEXT("Please try again!"));  //prompt to guess again
        return;
    }

    if (Lives <= 0)
    {
        PrintLine (TEXT("But you have run out of guesses!\nThe Game is over"));
        PrintLine (TEXT("\nThe Hidden Word was: %s "), *HiddenWord);
        bGameOver = true; // set the game over flag
        PrintLine (TEXT("Press Enter to Play again"));
        return;
    }

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index +1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
            
        }
    }
    
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count; //instantiate struct - ensures bulls and cows are set to 0 in .h file

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess [GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++; // increments value of bulls from .h file
            continue; // continues looping this loop rather than the next one if it's found a match
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess [GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++; // increments value of cows from .h file
                break; // avoids wasting time on addiitonal loops once it finds a match
            }
        }
        
    }

    return Count; //returns the value of both bull and cow counts
    
}

 