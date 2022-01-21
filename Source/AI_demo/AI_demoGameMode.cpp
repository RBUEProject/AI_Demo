// Copyright Epic Games, Inc. All Rights Reserved.

#include "AI_demoGameMode.h"
#include "AI_demoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAI_demoGameMode::AAI_demoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
