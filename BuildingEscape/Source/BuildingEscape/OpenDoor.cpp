// Copyright Ben Tarrant 2020


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

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
	//TriggerActor = GetWorld() -> GetFirstPlayerController() -> GetPawn(); //Sets the AActor Trigger Actor to be the Default Spawned Pawn of the player controller
	// GetWorld is a top down look, getting all classes, then getting player controller then pawn which inherits from Actors

	//Set Values for Door to Open
	InitialYaw = GetOwner() -> GetActorRotation().Yaw; // Checks initial Z rotation of the owner actor
	CurrentYaw = InitialYaw; // sets current to same as above - starting rotation of Z of owner
	TargetYaw += InitialYaw; // our target to LERP to is wherever the Z started + value defined in header/editor Target = Target + Initial

	FindPressurePlate(); //Check if a pressure plate has been assigned
	FindAudioComponent(); //Check if an Audio Component has been added
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//check if a pressure plate is assigned and have the player/trigger actor inside its volume
	if (PressurePlate && TotalMassOfActors() >= PressurePlateTargetMass) // if the pressure plate volume exists AND notes a mass of actors overlapping that's equal or greater than taregt trigger mass
	{
		OpenDoor(DeltaTime); //open the door (managed by delta time)
		DoorLastOpened = GetWorld() -> GetTimeSeconds();
	}

	else if (GetWorld() -> GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::FindPressurePlate()
{
	
	if (!PressurePlate) //if there is no assigned pressure plate actor
	{
		UE_LOG(LogTemp, Error, TEXT("The Actor %s has OpenDoor attached but no PressurePlate assigned"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG (LogTemp, Error, TEXT("%s is Missing an Audio Component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::OpenDoor (float DeltaTime)
{
	
	FRotator DoorRotation = GetOwner() -> GetActorRotation(); // container for rotation information
	CurrentYaw = FMath :: FInterpTo (CurrentYaw, TargetYaw, DeltaTime, OpenSpeed); // takes current yaw from BeginPlay and interpolates the current yaw to the target yaw managed by delta time
	DoorRotation.Yaw = CurrentYaw; //container's z rotation should = the current yaw each frame - gets updated by the interpolation above
	GetOwner() -> SetActorRotation(DoorRotation); // sets our owners rotation to = the rotators rotation each frame, thus opening the door

	CloseAudioPlayed = false;
	if (!AudioComponent) { return; }
	if (!OpenAudioPlayed) { AudioComponent->Play(); }
	OpenAudioPlayed = true;


	UE_LOG (LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation(). ToString()); 
	//Log, Yellow Text, Text Macro, String. GetActor this is attached, get its rotation, covert to string
	UE_LOG (LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);
}

void UOpenDoor::CloseDoor (float DeltaTime)
{
	OpenAudioPlayed = false;
	if (!AudioComponent) { return; }
	if (!CloseAudioPlayed) { AudioComponent->Play(); }
	CloseAudioPlayed = true;

	FRotator DoorRotation = GetOwner() -> GetActorRotation(); // container for rotation information
	CurrentYaw = FMath :: FInterpTo (CurrentYaw, InitialYaw, DeltaTime, CloseSpeed); // takes current yaw from BeginPlay and interpolates the current yaw to the target yaw managed by delta time
	DoorRotation.Yaw = CurrentYaw; //container's z rotation should = the current yaw each frame - gets updated by the interpolation above
	GetOwner() -> SetActorRotation(DoorRotation); // sets our owners rotation to = the rotators rotation each frame, thus opening the door


	//UE_LOG (LogTemp, Warning, TEXT("%s"), *GetOwner() -> GetActorRotation(). ToString()); 
	//Log, Yellow Text, Text Macro, String. GetActor this is attached, get its rotation, covert to string
	//UE_LOG (LogTemp, Warning, TEXT("Yaw: %f"), GetOwner() -> GetActorRotation().Yaw);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName());
	}

	return TotalMass;
}