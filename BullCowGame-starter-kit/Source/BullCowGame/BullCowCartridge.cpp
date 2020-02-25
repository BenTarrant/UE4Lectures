// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("LIME");
    Lives = HiddenWord.Len();
    bGameOver = false; // ensure the game over flag is clear

    //Intro Text
    PrintLine(TEXT("The Hidden Word is: %s "), *HiddenWord); //debug line
    PrintLine(TEXT("Hello there, Press Tab to use the Terminal")); // Prints a line to the terminal
    PrintLine(TEXT("You need to guess the %i letter word\nYou have %i Attempts"), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type in your Guess\nThen press enter..."));
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Begin Game
    Super::BeginPlay();
    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ProcessGuess(Input);
}

void UBullCowCartridge::LoseLife()
{
    if (Lives > 0)
    {
        --Lives; //minus a life

        PrintLine (TEXT("That was incorrect"));  
        PrintLine(TEXT("the word is %i letters long\nYou have %i Lives left"), HiddenWord.Len(), Lives);
        PrintLine (TEXT("Please try a new guess"));  //prompt to guess again
    }

    else
    {
        PrintLine (TEXT("That was incorrect"));
        PrintLine (TEXT("And you have run out of lives!\nGame Over"));
        bGameOver = true; // set the game over flag
        PrintLine (TEXT("Press Enter to Play again"));
    } 
}


void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (bGameOver != true) //if the game is not over
    {
        ClearScreen(); // clear the terminal
         //check the guess
        //is it an isogram?
        //is is the right amount of characters?

        PrintLine(TEXT("You guessed: " + (Guess)));
    
        if (Guess == HiddenWord)
        {
            // success state
            PrintLine(TEXT("Well done, that was correct!"));
            PrintLine(TEXT("You Win!"));
            bGameOver = true; // set the game over flag
            PrintLine (TEXT("Press Enter to Play again"));

        }

        else
        {

            if (Guess.Len() != HiddenWord.Len())
            {
                PrintLine (TEXT("The hidden word is %i characters long"), HiddenWord.Len());
            }

            LoseLife(); //remove a life function
        }
    }

    else // if the game IS over
    {
        ClearScreen(); // clear the terminal
        SetupGame(); // reset the game
    }
}
