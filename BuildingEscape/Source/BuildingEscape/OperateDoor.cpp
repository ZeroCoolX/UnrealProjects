// Copyright ZeroCoolDev 2016

#include "BuildingEscape.h"
#include "OperateDoor.h"

#define OUT


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
    
    //get owner which many methods need
    owner = GetOwner();
    
    if(!pressurePlate){
        //physics hangle is not found
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
    }
}

float UOperateDoor::GetTotalMassOnPlate(){
    float totalMass = 0.f;
    TArray<AActor *> actorsOnPlate;
    
    //nullptr check
    if(!pressurePlate){return totalMass;}

    //find all overlapping actors
    pressurePlate->GetOverlappingActors(OUT actorsOnPlate);
    
    //iterate addign all their masses
    for(const auto& actor : actorsOnPlate){
        totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *actor->GetName());
    }
    return totalMass;
}


// Called every frame
void UOperateDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    //Poll the trigger every frame
    if(GetTotalMassOnPlate() >= triggerMass){
        UE_LOG(LogTemp, Warning, TEXT("Opening door because the trigger was activated!!"));
        OnOpen.Broadcast();
    }else{
        OnClose.Broadcast();
    }
    
}

