// Fill out your copyright notice in the Description page of Project Settings.

#include "RunningShape.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"


// Sets default values
ARunningShape::ARunningShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("RootC"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshC"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void ARunningShape::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARunningShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

