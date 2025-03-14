// Copyright Epic Games, Inc. All Rights Reserved.

#include "prototype1GameMode.h"
#include "prototype1Character.h"
#include "UObject/ConstructorHelpers.h"

Aprototype1GameMode::Aprototype1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}