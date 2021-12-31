// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WizardBrawl.h"
#include "WBGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDBRAWL_API UWBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EWBAbilityInputID AbilityInputID = EWBAbilityInputID::None;
	
};
