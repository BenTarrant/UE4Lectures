// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hello there, Press Tab to use the Terminal")); // Prints a line to the terminal
    PrintLine(TEXT("Guess the 4 letter word\n Then press enter...")); // hard coded length of number but remove later
    HiddenWord = TEXT("LIME");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen(); // clear the terminal
    PrintLine(TEXT ("You guessed: " + (Input)));
    
        if (Input == HiddenWord)
    {
        PrintLine("Well done, that was correct!");
    }

    else
    {
      PrintLine ("That was incorrect, please try again");
    }

}

void CheckGuess()
{


}