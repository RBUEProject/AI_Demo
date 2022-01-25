// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class AI_DEMO_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolPath();

	FVector get_patrol_point(const int index)const;
	int num()const;
	void AddPatrolPathPoint(FVector const& NewPoint);
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AI",meta = (MakeEditWidget = "true",AllowPrivateAccess = "true"))
	TArray<FVector>patrol_points;
};
