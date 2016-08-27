// Copyright ZeroCoolDev 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!!"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    FVector playerLoc;
    FRotator playerRot;

	// Get player view point this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLoc, OUT playerRot);
    
    //Draww a red debug line for testing
    FVector lineTraceEnd = playerLoc + playerRot.Vector()*playerReach;
    DrawDebugLine(GetWorld(),//world
                  playerLoc,//start
                  lineTraceEnd,//end
                  FColor(0,255,0),
                  false,//persistence
                  0.f,
                  0.f,
                  5.f//thickness
                  );
    
    //Log out to test
    //UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *playerLoc.ToString(), *playerRot.ToString());
    
    //Setup query parameters
    FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
    
    FHitResult lineTraceHit;
    //Ray-cast outward till reach distance (need priv var for dist)
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT lineTraceHit,
                                            playerLoc,
                                            lineTraceEnd,
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            traceParams
                                            );
    
    
    //log what we hit
    AActor* actorHit = lineTraceHit.GetActor();
    if(actorHit){
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit->GetName()));
    }
}

