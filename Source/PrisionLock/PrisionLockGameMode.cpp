// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrisionLockGameMode.h"
#include "PrisionLockCharacter.h"
#include "UObject/ConstructorHelpers.h"

APrisionLockGameMode::APrisionLockGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
