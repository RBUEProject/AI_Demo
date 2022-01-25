// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"
UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& object_initilizer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (ACharacter*const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		FVector const player_location = player->GetActorLocation();
	
		if (search_random)
		{
			FNavLocation loc;

			if (UNavigationSystemV1*const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
				{
					owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), loc.Location);
				}
			}
		}
		else
		{
			owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), player_location);
		}
		FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
