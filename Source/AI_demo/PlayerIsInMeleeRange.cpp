// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIsInMeleeRange.h"
#include "NPC_AIController.h"
#include "NPC.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework//Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "blackboard_keys.h"
UPlayerIsInMeleeRange::UPlayerIsInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("is player in melee range");
}

void UPlayerIsInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp,node_memory);
	ANPC_AIController*const cont = Cast<ANPC_AIController>(owner_comp.GetAIOwner());
	ANPC*const npc = Cast<ANPC>(cont->GetPawn());

	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	cont->get_blackboard()->SetValueAsBool(GetSelectedBlackboardKey(),
		npc->GetDistanceTo(player)<=melee_range);
}
