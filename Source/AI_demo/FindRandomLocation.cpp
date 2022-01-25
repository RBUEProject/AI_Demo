// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NPC_AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (auto const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner()))
	{
		if (auto const npc = cont->GetPawn())
		{
			FVector const origin = npc->GetActorLocation();

			if (UNavigationSystemV1*const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation loc;
				if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
				{
					owner_comp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),loc.Location);
				}
			}
			FinishLatentTask(owner_comp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
