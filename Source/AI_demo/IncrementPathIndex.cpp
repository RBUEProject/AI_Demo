// Fill out your copyright notice in the Description page of Project Settings.


#include "IncrementPathIndex.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "blackboard_keys.h"
#include <cmath>
UIncrementPathIndex::UIncrementPathIndex(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Increase patrol Path Point Index");
}

EBTNodeResult::Type UIncrementPathIndex::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8*node_memory)
{
	//get AI controller
	if (ANPC_AIController*const controller = Cast<ANPC_AIController>(owner_comp.GetAIOwner()))
	{
		if (ANPC* const npc = Cast<ANPC>(controller->GetPawn()))
		{
	
			const int no_of_points = npc->get_patrol_path()->num();
			int const min_index = 0;
			int const max_index = no_of_points-1;
		
			int index = owner_comp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());
			if (bidirectional)
			{
				if (index >= max_index && direction == EDirectionType::Forward)
				{
					direction = EDirectionType::Reverse;
				}
				else if (index == min_index && direction == EDirectionType::Reverse)
				{
					direction = EDirectionType::Forward;
				}
			}
			owner_comp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(),
				(direction == EDirectionType::Forward ? std::abs(++index) : std::abs(--index))%no_of_points);
		
			FinishLatentTask(owner_comp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
