// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Cpp_AI_CharacterBase.generated.h"

UCLASS()
class AI_DEMO_API ACpp_AI_CharacterBase : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACpp_AI_CharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void attack_start();
	virtual void attack_end();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent*right_first_collision_box;
};
