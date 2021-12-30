#include "AbilityTypes.h"

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTypes.h"

FGameplayAbilityInfo::FGameplayAbilityInfo()
    :CooldownDuration(0),

    AbilityClass(nullptr)
{
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCooldownDuration, TSubclassOf<UGameplayAbilityBase> InAbilityClass)
    :CooldownDuration(InCooldownDuration),
   AbilityClass(InAbilityClass)
{
}
