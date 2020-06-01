// Copyright Ben Tarrant 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets default values for this component's properties
	UOpenDoor();

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	void FindAudioComponent();
	void FindPressurePlate();

	bool OpenAudioPlayed = false;
	bool CloseAudioPlayed = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float InitialYaw;
	float CurrentYaw;

	UPROPERTY(EditAnywhere) // exposes the below variables to the Editor
	float TargetYaw = 90;

	UPROPERTY(EditAnywhere) // exposes the below variables to the Editor
	float OpenSpeed = 2;
		
	UPROPERTY(EditAnywhere) // exposes the below variables to the Editor
	float CloseSpeed = 2.5;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	float TotalMassOfActors() const;

	UPROPERTY(EditAnywhere)
	float PressurePlateTargetMass = 50.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;


};
