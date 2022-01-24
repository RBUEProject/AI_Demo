// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NPC_AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"
UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& object_initilizer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	ACharacter*const player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	auto const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner());

	FVector const player_location = player->GetActorLocation();

	if (search_random)
	{
		FNavLocation loc;
		UNavigationSystemV1*const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(GetSelectedBlackboardKey(),loc.Location);
		}
	}
	else
	{
		cont->get_blackboard()->SetValueAsVector(GetSelectedBlackboardKey(), player_location);
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
