#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PlayerIsInMeleeRange.generated.h"

/**
 * 
 */
UCLASS()
class AI_DEMO_API UPlayerIsInMeleeRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UPlayerIsInMeleeRange();

	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI" , meta = (AllowPrivateAccess = "true"))
	float melee_range = 25.0f;
};
