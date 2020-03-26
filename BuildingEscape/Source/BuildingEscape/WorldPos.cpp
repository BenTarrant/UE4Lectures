// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPos.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

// Sets default values for this component's properties
UWorldPos::UWorldPos()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPos::BeginPlay()
{
	Super::BeginPlay();

	// FString Log = TEXT("Hello!"); //Create an initialise Fstring variable called Log
	// FString* PtrLog = &Log; //Create a pointer that points to the address of Log in memory
	// PtrLog -> Len(); //Derefernece the item in memory to address member variables like Len using PtrName -> MemberVariable();  could also use (*PtrName).MemberVariable();
	// UE_LOG (LogTemp, Warning, TEXT("%s"), **PtrLog);

	
	FString ActorName = GetOwner() -> GetName(); //Decalre Fstring variable called ActorName, use the pointer function get owner and get name
	UE_LOG (LogTemp, Warning, TEXT("This componment is attached to: %s"), *ActorName); //print the dereferenced value of what is pointed at (Actor Name)

	FString ActorTransform = GetOwner() -> GetActorLocation().ToString(); //Fstring variable ActorTransform, use pointer to point to owner then grab the vector of location - covert Vector to String
	UE_LOG (LogTemp, Warning, TEXT("This componment is located at: %s"), *ActorTransform); //Print the dereferenced value of the ActorLocation to log
	// ...
	
}


// Called every frame
void UWorldPos::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

