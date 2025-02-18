// Copyright ZeroCoolDev 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    
private:
    //how far ahead of the player we can reach
    float playerReach = 100.f;
    
    UPhysicsHandleComponent* physicsHandle = nullptr;// nullptr is mermory address 0
    
    UInputComponent* inputComponent = nullptr;
    
    //raycast and grab what's in reach
    void Grab();
    
    //Called when grab is released
    void Released();
    
    //find attached physics handle
    void SetupPhysicsHandleComponent();
    
    //find the input component
    void SetupInputComponent();
    
    //return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBody();
    
    //get raycast from player to its reach outward
    FVector CalculateReachLineEnd();
    
    //get the players location
    FVector GetPlayerLocation();
	
};
