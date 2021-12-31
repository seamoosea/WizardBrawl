// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WBAbilitySystemComponent.h"
#include "WBAttributeSet.h"
#include "WBGameplayAbility.h"
#include <GameplayEffectTypes.h>
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "WizardBrawlCharacter.generated.h"

class UAttributeSetBase;
class UGameplayAbilityBase;


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

    // Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//virtual void InitializeAttributes();

    // Called to bind functionality to input
    //virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
        void AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire);

   // UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
     //   void AcquireAbilities(TArray<TSubclassOf<UWBGameplayAbility>> AbilityToAcquire);

    //acquire abilities above

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

    UFUNCTION(BlueprintCallable, Category = Ability)
   virtual FGameplayAbilitySpecHandle GiveAbilityToInputID(TSubclassOf<UGameplayAbility> Ability, int Level, int32 InputId = -1);



    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WizardBrawlCharacter")
    class UWBAbilitySystemComponent* AbilitySystemComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WizardBrawlCharacter")
    class UWBAttributeSet* Attributes;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WizardBrawlCharacter")
    TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;


    uint8 GetTeamID() const;

    UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
        void AddGameplayTag(FGameplayTag& TagToAdd);
    UFUNCTION(BlueprintCallable, Category = "WizardBrawlCharacter")
      void RemoveGameplayTag(FGameplayTag& TagToRemove);


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


};

