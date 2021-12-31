// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WBAbilitySystemComponent.h"
#include "WBAttributeSet.h"
#include "WBGameplayAbility.h"
#include <GameplayEffectTypes.h>
#include "WizardBrawlCharacter.generated.h"


UCLASS(Blueprintable)
class WIZARDBRAWL_API AWizardBrawlCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWizardBrawlCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BindASCInput();

    UFUNCTION(BlueprintCallable, Category = "CharacterBase")
        void AcquireAbility(TSubclassOf<UWBGameplayAbility> AbilityToAcquire);
    UFUNCTION(BlueprintCallable, Category = "CharacterBase")
        void AcquireAbilities(TArray<TSubclassOf<UWBGameplayAbility>> AbilityToAcquire);

    //acquire abilities above

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

    uint8 GetTeamID() const;

    UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
      void AddGameplayTag(FGameplayTag& TagToAdd);
    UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
      void RemoveGameplayTag(FGameplayTag& TagToRemove);


};

