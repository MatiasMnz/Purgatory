// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() )
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	    PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
    FHitResult HitResult;
	bool HasHit=GetGrabbleInReach(HitResult);

if (HasHit)
{
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	HitComponent->WakeAllRigidBodies();
	HitComponent->SetSimulatePhysics(true);
	AActor* HitActor = HitResult.GetActor();
	HitActor-> Tags.Add("Grabbed");
	HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    PhysicsHandle->GrabComponentAtLocationWithRotation(
    HitResult.GetComponent(),
	NAME_None,
    HitResult.ImpactPoint,
	GetComponentRotation()
	);
}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor-> Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()-> FindComponentByClass <UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requieres a UphysicsHandleComponent."));
	}
	return Result;
}

bool UGrabber :: GetGrabbleInReach(FHitResult& OutHitResult) const
{
	
	//FRotator MyRotation = GetComponentRotation();
	//FString RotationString = MyRotation.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Grabber Rotation %s"), *RotationString);
	//float Time = GetWorld()->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("Current Time Is: %f"), Time); - Rotacion de Camara
    FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
    //DrawDebugLine(GetWorld(), Start, End, FColor::Transparent); - Laser de referencia para "Debug"
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
    OutHitResult,
	Start, End,
	FQuat::Identity, 
	ECC_GameTraceChannel2,
	Sphere);
}