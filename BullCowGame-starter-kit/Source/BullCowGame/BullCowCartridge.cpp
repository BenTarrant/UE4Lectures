// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Begin Game
    Super::BeginPlay();
    PrintLine(TEXT("Hello there, Press Tab to use the Terminal")); // Prints a line to the terminal
    PrintLine(TEXT("Guess the 4 letter word\n Then press enter...")); // hard coded length of number but remove later

    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen(); // clear the terminal

    //check the guess
    //is it an isogram?
    //is is the right amount of characters?

    PrintLine(TEXT ("You guessed: " + (Input)));
    
        if (Input == HiddenWord)
    {
        PrintLine("Well done, that was correct!");
    }

    else
    {
      PrintLine ("That was incorrect, please try again");
      //Lives -1;
      PrintLine ((Lives) + "Lives Remaining ");
      PrintLine ("Please guess again");

      //remove a life
      //show how many lives remaining
      //prompt to guess again
    }

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("LIME");
    Lives = 3;
}