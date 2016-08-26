// Copyright ZeroCoolDev 2016

#include "BuildingEscape.h"
#include "OperateDoor.h"


// Sets default values for this component's properties
UOperateDoor::UOperateDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOperateDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOperateDoor::OpenDoor(){
    //get owner
    AActor* owner = GetOwner();
    
    //create a rotator
    FRotator newRotation = FRotator(0.0f, 60.0f, 0.0f);
    
    //set door rotation
    UE_LOG(LogTemp, Warning, TEXT("Setting rotation"));
    owner->SetActorRotation(newRotation);
}


// Called every frame
void UOperateDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll the trigger every frame
    if(pressurePlate->IsOverlappingActor(actorThatOpens)){
    
    }
   /* if(pressurePlate->IsOverlappingActor(actorThatOpens)){
        UE_LOG(LogTemp, Warning, TEXT("Opening door because the trigger was activated!!"));
        OpenDoor();
    }*/
}

