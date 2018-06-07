// Fill out your copyright notice in the Description page of Project Settings.

#include "GeometryRunGameModeBase.h"
#include "PlayerPawn.h"


AGeometryRunGameModeBase::AGeometryRunGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
}

