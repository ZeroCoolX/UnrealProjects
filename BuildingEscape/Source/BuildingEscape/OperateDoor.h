// Copyright ZeroCoolDev 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OperateDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOperateDoor : public UActorComponent
{
    GENERATED_BODY()
    
public:
    // Sets default values for this component's properties
    UOperateDoor();
    
    // Called when the game starts
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
    //opens a door 90 degrees
    void OpenDoor();
    
    //close a door 90 degrees
    void CloseDoor();
    
    
private:
    UPROPERTY(VisibleAnywhere)
    float openAngle = 90.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* pressurePlate;
    
    AActor* owner;
    
    UPROPERTY(EditAnywhere)
    float doorCloseDelay = 1.0f;
    
    float lastDoorOpenTime;
    
    //float triggerMassThreshhold = 100.f;
    
    float GetTotalMassOnPlate();
};
