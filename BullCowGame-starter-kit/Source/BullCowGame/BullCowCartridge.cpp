// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hello there, Press Tab to use the Terminal\nThen press enter to continue..")); // Prints a line to the terminal
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen(); // clear the terminal
    FString HiddenWord = TEXT("LIME");
    PrintLine(TEXT ("You guessed: " + (Input)));
}