// Copyright Ben Tarrant 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	InitialYaw = GetOwner() -> GetActorRotation().Yaw; // Checks initial Z rotation of the owner actor
	CurrentYaw = InitialYaw; // sets current to same as above - starting rotation of Z of owner
	TargetYaw += InitialYaw; // our target to LERP to is wherever the Z started + value defined in header/editor Target = Target + Initial
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//UE_LOG (LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation(). ToString()); 
	// Log, Yellow Text, Text Macro, String. GetActor this is attached, get its rotation, covert to string

	//UE_LOG (LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);

	FRotator DoorRotation = GetOwner() -> GetActorRotation(); // container for rotation information
	CurrentYaw = FMath :: FInterpTo (CurrentYaw, TargetYaw, DeltaTime, 2); // takes current yaw from BeginPlay and interpolates the current yaw to the target yaw managed by delta time
	DoorRotation.Yaw = CurrentYaw; //container's z rotation should = the current yaw each frame - gets updated by the interpolation above
	GetOwner() -> SetActorRotation(DoorRotation); // sets our owners rotation to = the rotators rotation each frame, thus opening the door
}

