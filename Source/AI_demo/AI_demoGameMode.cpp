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
	static ConstructorHelpers::FClassFinder<ANPC>npc(TEXT("Blueprint'/Game/AI/NPC_BP'"));
	if (npc.Succeeded())
	{
		FNPC_Class = npc.Class;
	}
	static ConstructorHelpers::FClassFinder<APatrolPath>Patrol(TEXT("Blueprint'/Game/AI/BP_PatrolPath'"));
	if (Patrol.Succeeded())
	{
		FPatrolPath_Class = Patrol.Class;
	}
}

void AAI_demoGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (FNPC_Class && FPatrolPath_Class)
	{
		FVector const NPC_loc{-970.002380,950.000000,218.001297};
		FVector const PatrolPath_loc{-809.419312,630.861877,152.631042};
		FActorSpawnParameters const params;
		if (auto const path = GetWorld()->SpawnActor<APatrolPath>(FPatrolPath_Class, PatrolPath_loc, FRotator::ZeroRotator, params))
		{
			path->AddPatrolPathPoint(FVector{-460.000000,179.999939,0.000000});
			path->AddPatrolPathPoint(FVector{200.000000,100.000000,0.000000});
			path->AddPatrolPathPoint(FVector{1450.000000,-1100.000000,270.000000});
			path->AddPatrolPathPoint(FVector{-690.000000,-1400.000000,310.000000});
			if (auto const npc = GetWorld()->SpawnActor<ANPC>(FNPC_Class, NPC_loc, FRotator::ZeroRotator, params))
			{
				npc->SetPatrolPath(path);
			}
		}
	}
}
