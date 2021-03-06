// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Animation/AnimMontage.h"
#include "Sound/SoundBase.h"
#include "Cpp_AI_CharacterBase.h"
#include "AI_demoCharacter.generated.h"

UCLASS(config=Game)
class AAI_demoCharacter : public ACpp_AI_CharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AAI_demoCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	void BeginPlay()override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	float get_health()const;
	float get_max_health()const;
	void set_health(float const new_health);

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	void Tick(float const DeltaTime)override;
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UWidgetComponent*widget_component;
	float health;
	float const max_health = 100.0f;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Sound",meta = (AllowPrivateAccess = "true"))
	USoundBase*distraction_sound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation",meta = (AllowPrivateAccess = "true"))
	UAnimMontage*montage;



	void OnExitGame();

	class UAIPerceptionStimuliSourceComponent*stimulus;

	void setup_stimulus();

	void on_attack();
	void on_distract();

	UFUNCTION()
	void on_attack_overlap_begin(UPrimitiveComponent*const overlapped_component, AActor*const other_actor,
		UPrimitiveComponent*other_component, int const other_body_index, bool const from_sweep, FHitResult const& sweep_result);
	UFUNCTION()
	void on_attack_overlap_end(UPrimitiveComponent*const overlapped_component, AActor*const other_actor,
		UPrimitiveComponent*other_component, int const other_body_index);
};

