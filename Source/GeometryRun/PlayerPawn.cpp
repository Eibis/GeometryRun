// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	QueryParams.AddIgnoredActor(this);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector position = GetActorLocation();

	if (bToMove)
	{
		position += NewPosition * DeltaTime;

		SetActorLocation(position);
	
		NewPosition.Set(0.0f, 0.0f, 0.0f);
		bToMove = false;
	}

	FHitResult hit = FHitResult(ForceInit);
	bool collided = GetWorld()->SweepSingleByChannel(hit, position, position, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, FCollisionShape::MakeSphere(CheckSphereRadius), QueryParams);

	if (collided)
	{
		FRotator rotation = FRotationMatrix::MakeFromZ(hit.ImpactNormal).Rotator();

		FVector relative_up = rotation.Quaternion().GetUpVector();

		FVector direction = InputRotation.Quaternion().GetForwardVector().GetSafeNormal();

		float angle_xy = FMath::Atan2(direction.Y, direction.X) - FMath::Atan2(relative_up.Y, relative_up.X);

		FRotator horizontal_adjustment = FQuat(relative_up, angle_xy).Rotator();

		rotation = UKismetMathLibrary::ComposeRotators(rotation, horizontal_adjustment);

		position = hit.ImpactPoint + GroundOffset;

		DrawDebugSphere(GetWorld(), position, CheckSphereRadius, 12, FColor::Green, false, DeltaTime * 2.0f);

		SetActorLocationAndRotation(position, rotation);
	}
	else
		DrawDebugSphere(GetWorld(), position, CheckSphereRadius, 12, FColor::Red, false, DeltaTime * 2.0f);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("HorizontalMovement", this, &APlayerPawn::HorizontalMovement);
	PlayerInputComponent->BindAxis("VerticalMovement", this, &APlayerPawn::VerticalMovement);

	PlayerInputComponent->BindAxis("HorizontalRotation", this, &APlayerPawn::HorizontalRotation);
	PlayerInputComponent->BindAxis("VerticalRotation", this, &APlayerPawn::VerticalRotation);
}

void APlayerPawn::HorizontalMovement(float amount)
{
	if (FMath::IsNearlyZero(amount))
		return;

	const FVector& right = UKismetMathLibrary::GetRightVector(GetActorRotation());

	NewPosition += right * amount * Speed;

	bToMove = true;
}

void APlayerPawn::VerticalMovement(float amount)
{
	if (FMath::IsNearlyZero(amount))
		return;

	const FVector& forward = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	
	NewPosition += forward * amount * Speed;

	bToMove = true;
}

void APlayerPawn::HorizontalRotation(float amount)
{
	if (FMath::IsNearlyZero(amount))
		return;

	InputRotation.Add(0.0f, RotationSpeed * amount, 0.0f);

	bToMove = true;
}

void APlayerPawn::VerticalRotation(float amount)
{
	if (FMath::IsNearlyZero(amount))
		return;

	bToMove = true;
}