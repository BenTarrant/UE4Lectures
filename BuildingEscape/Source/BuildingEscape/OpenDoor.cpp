// Copyright Ben Tarrant 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Assign player as TriggerActor to open Door
	TriggerActor = GetWorld() -> GetFirstPlayerController() -> GetPawn(); //Sets the AActor Trigger Actor to be the Default Spawned Pawn of the player controller
	// GetWorld is a top down look, getting all classes, then getting player controller then pawn which inherits from Actors

	//Set Values for Door to Open
	InitialYaw = GetOwner() -> GetActorRotation().Yaw; // Checks initial Z rotation of the owner actor
	CurrentYaw = InitialYaw; // sets current to same as above - starting rotation of Z of owner
	TargetYaw += InitialYaw; // our target to LERP to is wherever the Z started + value defined in header/editor Target = Target + Initial

	//Check if a pressure plate has been assigned
	if (!PressurePlate) //if there is no assigned pressure plate actor
	{
		UE_LOG (LogTemp, Error, TEXT("The Actor %s has OpenDoor attached but no PressurePlate assigned"), *GetOwner() -> GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//check if a pressure plate is assigned and have the player/trigger actor inside its volume
	if (PressurePlate && PressurePlate -> IsOverlappingActor(TriggerActor)) // if the pressure plate volume exists AND notes an actor overlapping that's the specified trigger actor
	{
		OpenDoor(DeltaTime); //open the door (managed by delta time)
	}

	else
	{
		CloseDoor(DeltaTime);
	}

}

void UOpenDoor::OpenDoor (float DeltaTime)
{
	FRotator DoorRotation = GetOwner() -> GetActorRotation(); // container for rotation information
	CurrentYaw = FMath :: FInterpTo (CurrentYaw, TargetYaw, DeltaTime, OpenSpeed); // takes current yaw from BeginPlay and interpolates the current yaw to the target yaw managed by delta time
	DoorRotation.Yaw = CurrentYaw; //container's z rotation should = the current yaw each frame - gets updated by the interpolation above
	GetOwner() -> SetActorRotation(DoorRotation); // sets our owners rotation to = the rotators rotation each frame, thus opening the door

	UE_LOG (LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation(). ToString()); 
	//Log, Yellow Text, Text Macro, String. GetActor this is attached, get its rotation, covert to string
	UE_LOG (LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);
}

void UOpenDoor::CloseDoor (float DeltaTime)
{
	FRotator DoorRotation = GetOwner() -> GetActorRotation(); // container for rotation information
	CurrentYaw = FMath :: FInterpTo (CurrentYaw, InitialYaw, DeltaTime, CloseSpeed); // takes current yaw from BeginPlay and interpolates the current yaw to the target yaw managed by delta time
	DoorRotation.Yaw = CurrentYaw; //container's z rotation should = the current yaw each frame - gets updated by the interpolation above
	GetOwner() -> SetActorRotation(DoorRotation); // sets our owners rotation to = the rotators rotation each frame, thus opening the door

	//UE_LOG (LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation(). ToString()); 
	//Log, Yellow Text, Text Macro, String. GetActor this is attached, get its rotation, covert to string
	//UE_LOG (LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);
}