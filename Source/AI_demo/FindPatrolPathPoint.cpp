// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPatrolPathPoint.h"
#include "NPC_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NPC.h"
#include "blackboard_keys.h"

UFindPatrolPathPoint::UFindPatrolPathPoint(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Patrol Path Point");
}

EBTNodeResult::Type UFindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8*node_memory)
{
	if (ANPC_AIController*const controller = Cast<ANPC_AIController>(owner_comp.GetAIOwner()))
	{
		int const index  = owner_comp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());
		
		if (ANPC*const npc = Cast<ANPC>(controller->GetPawn()))
		{
			FVector const point = npc->get_patrol_path()->get_patrol_point(index);//local
			FVector const global_point = npc->get_patrol_path()->GetActorTransform().TransformPosition(point);//global
			owner_comp.GetBlackboardComponent()->SetValueAsVector(PatrolPathVectorKey.SelectedKeyName,global_point);
			FinishLatentTask(owner_comp,EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
