// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotifyState.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Cpp_AI_CharacterBase.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ACpp_AI_CharacterBase*const character = Cast<ACpp_AI_CharacterBase>(MeshComp->GetOwner()))
		{
			character->attack_start();
		}
	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ACpp_AI_CharacterBase*const character = Cast<ACpp_AI_CharacterBase>(MeshComp->GetOwner()))
		{
			character->attack_end();
		}
	}
}
