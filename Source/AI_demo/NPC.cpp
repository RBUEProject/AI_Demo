// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"
#include "RunTime/Engine/Classes/Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework//PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "HealthBar.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "AI_demoCharacter.h"
// Sets default values
ANPC::ANPC():widget_component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue"))),health(max_health)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	if (widget_component)
	{
		widget_component->SetupAttachment(RootComponent);
		widget_component->SetWidgetSpace(EWidgetSpace::Screen);//face the player
		widget_component->SetRelativeLocation(FVector(0.0f, 0.0f, 85.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/UI/HeathBar_WBP"));
		if (widget_class.Succeeded())
		{
			widget_component->SetWidgetClass(widget_class.Class);
		}
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic*const material_instance = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	if (material_instance)
	{
		material_instance->SetVectorParameterValue("BodyColor", FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
		GetMesh()->SetMaterial(0, material_instance);
	}
	if (right_first_collision_box)
	{
		right_first_collision_box->OnComponentBeginOverlap.AddDynamic(this, &ANPC::on_attack_overlap_begin);
		right_first_collision_box->OnComponentEndOverlap.AddDynamic(this, &ANPC::on_attack_overlap_end);
	}
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto const uw = Cast<UHealthBar>(widget_component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent(health / max_health);
		//UE_LOG(LogTemp, Error, TEXT("update health bar"));
	}
}

float ANPC::get_health() const
{
	return health;
}

float ANPC::get_max_health() const
{
	return max_health;
}

void ANPC::set_health(float const new_health)
{
	health = new_health;
	if (health <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("You win"));
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

APatrolPath* ANPC::get_patrol_path()
{
	return patrol_path;
}


void ANPC::melee_attack()
{
	if (montage)
	{
		PlayAnimMontage(montage);
	}
}

UAnimMontage* ANPC::get_Montage() const
{
	return montage;
}

void ANPC::on_attack_overlap_begin(UPrimitiveComponent*const overlapped_component, AActor*const other_actor, UPrimitiveComponent*other_component, int const other_body_index, bool const from_sweep, FHitResult const& sweep_result)
{
	if (AAI_demoCharacter* const player = Cast<AAI_demoCharacter>(other_actor))
	{
		float const new_health = player->get_health() - player->get_max_health()*0.1f;
		player->set_health(new_health);
	}
}

void ANPC::on_attack_overlap_end(UPrimitiveComponent*const overlapped_component, AActor*const other_actor, UPrimitiveComponent*other_component, int const other_body_index)
{
	
}