// Fill out your copyright notice in the Description page of Project Settings.


#include "Cpp_AI_CharacterBase.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
// Sets default values
ACpp_AI_CharacterBase::ACpp_AI_CharacterBase():
right_first_collision_box(CreateDefaultSubobject<UBoxComponent>(TEXT("RightFirstCollisionBox")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (right_first_collision_box)
	{
		FVector const extent(7.0f);
		right_first_collision_box->SetBoxExtent(extent, false);
		right_first_collision_box->SetCollisionProfileName("NoCollision");
	}
}

// Called when the game starts or when spawned
void ACpp_AI_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (right_first_collision_box) {
		FAttachmentTransformRules const rules(EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
		right_first_collision_box->AttachToComponent(GetMesh(), rules, "hand_rSocket");
		right_first_collision_box->SetRelativeLocation(FVector(-7.0f, 0.0f, 0.0f));
	}

}

// Called every frame
void ACpp_AI_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACpp_AI_CharacterBase::attack_start()
{
	right_first_collision_box->SetCollisionProfileName("Fist");
	right_first_collision_box->SetNotifyRigidBodyCollision(true);
}

void ACpp_AI_CharacterBase::attack_end()
{
	right_first_collision_box->SetCollisionProfileName("NoCollision");
	right_first_collision_box->SetNotifyRigidBodyCollision(false);
}


