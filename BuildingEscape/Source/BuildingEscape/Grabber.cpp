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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	// Call the function to check necessary components have a physics handle
	FindPhysicsHandle();
	// Call the function to check necessary input components are present and assigned
	SetupInputComponent();
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
	
	if (PhysicsHandle -> GrabbedComponent)
	{
		PhysicsHandle -> SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	
	//variables for use in Playerviewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	//Get player viewpoint
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	//UE_LOG (LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	// raycast out to X distance (players reach)
	FVector LineTraceDirection = PlayerViewPointRotation.Vector() *Reach;
	FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection;
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
	FHitResult HitResult = RaycastHitResult();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	FRotator Test;

	if(HitResult.GetActor())
	{
		PhysicsHandle -> GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, LineTraceEnd, Test);
		
	}
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));

	if (PhysicsHandle ->GrabbedComponent)
	{
		PhysicsHandle -> ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle Released"));
	}
}

void UGrabber::FindPhysicsHandle()
{
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

void UGrabber::SetupInputComponent()
{
	InputHandle = GetOwner() -> FindComponentByClass<UInputComponent>();
	if (InputHandle)
	{
		UE_LOG (LogTemp, Warning, TEXT("The Actor %s has an Input Component"), *GetOwner() -> GetName());
		InputHandle -> BindAction("GrabItem", IE_Pressed, this, &UGrabber::Grab);
		InputHandle -> BindAction("GrabItem", IE_Released, this, &UGrabber::Release);
	}

	else
	{
		UE_LOG (LogTemp, Error, TEXT("The Actor %s has doesn't have an Input Component"), *GetOwner() -> GetName());
	}
}

FHitResult UGrabber::RaycastHitResult()
{
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
	GetWorld() -> LineTraceSingleByObjectType(
    OUT Hit,
    PlayerViewPointLocation,
    LineTraceEnd,
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    TraceParams);

	// check what we hit with the raycast and consider
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ray Hit: %s "), *(ActorHit -> GetName()));
	}

	return Hit;
}



