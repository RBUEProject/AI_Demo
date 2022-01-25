// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPC.h"
#include "PatrolPath.h"
#include "AI_demoGameMode.generated.h"

UCLASS(minimalapi)
class AAI_demoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAI_demoGameMode();
	void BeginPlay()override;
private:
	TSubclassOf<ANPC>FNPC_Class;
	TSubclassOf<APatrolPath>FPatrolPath_Class;
};



