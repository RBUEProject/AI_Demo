// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class AI_DEMO_API UChangeSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UChangeSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent&owner_comp,uint8*node_memory)override;
protected:
	FString GetStaticServiceDescription()const;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI" , meta = (AllowPrivateAccess = "true"))//使蓝图可以访问私有变量
	float speed = 600.0f;
};
