// Copyright ZeroCoolDev 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OperateDoor.generated.h"

//used for sending listenable events for blueprint interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);


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
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnClose;
    
private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* pressurePlate;
    
    AActor* owner;
    
    UPROPERTY(EditAnywhere)
    float triggerMass = 30.f;
    
    float GetTotalMassOnPlate();
};
