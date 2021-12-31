// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "WBAbilitySystemComponent.h"
#include "WBAttributeSet.h"
#include "WBPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDBRAWL_API AWBPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWBPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UWBAttributeSet* GetAttributeSet() const;

	virtual void InitializeAttributes();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		class UWBAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		class UWBAttributeSet* Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	
};
