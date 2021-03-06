// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "blackboard_keys.h"
#include "Perception/AIPerceptionComponent.h"
#include "ai_tags.h"
#include "NPC.h"
ANPC_AIController::ANPC_AIController(FObjectInitializer const& object_initializer)
{
	setup_perception_system();
}


void ANPC_AIController::OnPossess(APawn*const pawn)
{
	Super::OnPossess(pawn);
	if (auto const NPC = Cast<ANPC>(pawn))
	{
		if (UBehaviorTree*const Tree = NPC->GetBehaviorTree())
		{
			UseBlackboard(Tree->BlackboardAsset, BlackboardComponent);
			RunBehaviorTree(Tree);
			UE_LOG(LogTemp,Warning,TEXT("Run behavior Tree succeed"));
		}
	}
}


void ANPC_AIController::on_updated(TArray<AActor*>const& updated_actors)
{
	for (size_t x = 0;x<updated_actors.Num();++x)
	{
		FActorPerceptionBlueprintInfo info;
		GetPerceptionComponent()->GetActorsPerception(updated_actors[x],info);
		for (size_t k = 0; k < info.LastSensedStimuli.Num(); ++k)
		{
			FAIStimulus const stim = info.LastSensedStimuli[k];
			if (BlackboardComponent && stim.Tag == tags::noise_tag )
			{
				BlackboardComponent->SetValueAsBool(bb_keys::is_investigating,stim.WasSuccessfullySensed());
				BlackboardComponent->SetValueAsVector(bb_keys::target_location,stim.StimulusLocation);
			} 
			else if(BlackboardComponent && stim.Type.Name == "Default__AISense_Sight")
			{
				BlackboardComponent->SetValueAsBool(bb_keys::can_see_player,stim.WasSuccessfullySensed());
			}
		}
	}
}

void ANPC_AIController::setup_perception_system()
{
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (sight_config)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		sight_config->SightRadius = 1000.0f;
		sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
		sight_config->PeripheralVisionAngleDegrees = 90.0f;
		sight_config->SetMaxAge(5.0f);
		sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
		sight_config->DetectionByAffiliation.bDetectEnemies = 
		sight_config->DetectionByAffiliation.bDetectFriendlies = 
		sight_config->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
		GetPerceptionComponent()->ConfigureSense(*sight_config);
	}

	hearing_config = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	if (hearing_config)
	{
		hearing_config->HearingRange = 3000.0f;
		hearing_config->DetectionByAffiliation.bDetectEnemies = 
		hearing_config->DetectionByAffiliation.bDetectFriendlies = 
		hearing_config->DetectionByAffiliation.bDetectNeutrals = true;
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANPC_AIController::on_updated);
		GetPerceptionComponent()->ConfigureSense(*hearing_config);
	}
}
