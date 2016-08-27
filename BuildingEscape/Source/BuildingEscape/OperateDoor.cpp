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
}

void UOperateDoor::OpenDoor(){
    //set door rotation
    UE_LOG(LogTemp, Warning, TEXT("Opening door"));
    owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}

void UOperateDoor::CloseDoor(){
    //set door rotation
    //UE_LOG(LogTemp, Warning, TEXT("Closing door"));
    owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOperateDoor::GetTotalMassOnPlate(){
    float totalMass = 0.f;
    TArray<AActor *> actorsOnPlate;
    
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
    if(GetTotalMassOnPlate() >= 40.f){
        UE_LOG(LogTemp, Warning, TEXT("Opening door because the trigger was activated!!"));
        OpenDoor();
        lastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    //check if its time to close the door
    if(lastDoorOpenTime+doorCloseDelay < GetWorld()->GetTimeSeconds()){
        //UE_LOG(LogTemp, Warning, TEXT("Closing door because it was open too long"));
        CloseDoor();
    }
    
}

