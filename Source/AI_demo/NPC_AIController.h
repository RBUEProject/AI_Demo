// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPC_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_DEMO_API ANPC_AIController : public AAIController
{
	GENERATED_BODY()
public:
	ANPC_AIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	void OnPossess(APawn*const pawn)override;

private:
	UPROPERTY()
	UBlackboardComponent*BlackboardComponent;

	class UAISenseConfig_Sight* sight_config;

	class UAISenseConfig_Hearing* hearing_config;

	UFUNCTION()
	void on_updated(TArray<AActor*>const& updated_actors);

	void setup_perception_system();

};
