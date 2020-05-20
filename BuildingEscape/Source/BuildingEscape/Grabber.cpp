// Copyright Ben Tarrant 2020


#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// check for the physics handle component to enable grabbing
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		//Physics Handle Found
	}

	else
	{
		UE_LOG (LogTemp, Error, TEXT("The Actor %s has Grabber.cpp attached but no PhysicsHandle Component"), *GetOwner() -> GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//variables for use in Playerviewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	//Get player viewpoint
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	//UE_LOG (LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	// raycast out to X distance (players reach)
	FVector LineTraceDirection = PlayerViewPointRotation.Vector() *Reach;
	FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection;
	FHitResult Hit;
	FCollisionQueryParams TraceParams (FName(TEXT("")), false, GetOwner());

	//fire the raycast
	GetWorld() -> LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	//visualise the raycast
	DrawDebugLine(
	GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(255,0,0),
	false,
	0.f,
	0,
	3.f
	);
	
	// check what we hit with the raycast and consider
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Error, TEXT("Ray Hit: %s "), *(ActorHit -> GetName()));
	}
	
}

