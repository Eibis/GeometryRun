// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GEOMETRYRUN_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HorizontalMovement(float amount);
	void VerticalMovement(float amount);

	void HorizontalRotation(float amount);
	void VerticalRotation(float amount);

	UPROPERTY(EditAnywhere, Category = "Settings")
	float Speed = 250.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float RotationSpeed = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float CheckSphereRadius = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector GroundOffset = FVector(0.0f, 0.0f, 50.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector NewPosition;
	FRotator Rotation;

	FCollisionQueryParams QueryParams;

	bool bToMove = false;
};
