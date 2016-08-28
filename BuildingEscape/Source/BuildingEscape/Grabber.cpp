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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    
    ///Look for attached physics handle
    SetupPhysicsHandleComponent();
    
    //Look for attached input component
    SetupInputComponent();
}

void UGrabber::SetupInputComponent(){
    //Look for attached input component
    inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(inputComponent == nullptr){
        //physics hangle is not found
        UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
    }else{
        inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);//last param points to a funciton
        inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Released);//last param points to a funciton
    }
}

void UGrabber::SetupPhysicsHandleComponent(){
    ///Look for attached physics handle
    physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(physicsHandle == nullptr){
        //physics hangle is not found
        UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
    }
}

//when right mouse button is pressed
void UGrabber::Grab(){
    //Line trace and see if we reach any ators with physucs body collision
    auto hitResult = GetFirstPhysicsBody();
    auto componentToGrab = hitResult.GetComponent();
    auto actorHit = hitResult.GetActor();//used for redundant check to make sure there IS an actor to atttach to
    
    //nullptr check
    if(!physicsHandle){return;}
    
    //Attach the physics handle
    if(actorHit){
        physicsHandle->GrabComponent(componentToGrab,
                                 NAME_None,//no bones needed
                                 componentToGrab->GetOwner()->GetActorLocation(),
                                 true//allow rotation
                                 );
    }
}

//when right mouse button is released
void UGrabber::Released(){
    //nullptr check
    if(!physicsHandle){return;}
    
    //release physics body
    physicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBody(){
    //Setup query parameters
    FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
    
    FHitResult lineTraceHit;
    //Ray-cast outward till reach distance (need priv var for dist)
    GetWorld()->LineTraceSingleByObjectType(
                                            OUT lineTraceHit,
                                            GetPlayerLocation(),
                                            CalculateReachLineEnd(),
                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                            traceParams
                                            );
    //log what we hit
    AActor* actorHit = lineTraceHit.GetActor();
    if(actorHit){
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(actorHit->GetName()));
    }
    return lineTraceHit;
}

FVector UGrabber::CalculateReachLineEnd(){
    FVector playerLoc;
    FRotator playerRot;
    
    ///Get player view point this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLoc, OUT playerRot);
    
    return playerLoc + playerRot.Vector() * playerReach;
}

FVector UGrabber::GetPlayerLocation(){
    FVector playerLoc;
    FRotator playerRot;
    
    ///Get player view point this tick
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerLoc, OUT playerRot);
    return playerLoc;
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    //nullptr check
    if(!physicsHandle){return;}
    
    if(physicsHandle->GrabbedComponent){//if we're grabbing somehting currently, move it along the raycast
        physicsHandle->SetTargetLocation(CalculateReachLineEnd());
    }
}

