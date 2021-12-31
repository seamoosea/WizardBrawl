// Fill out your copyright notice in the Description page of Project Settings.


#include "WBAttributeSet.h"
#include "Net/UnrealNetwork.h"

UWBAttributeSet::UWBAttributeSet()
{

}

void UWBAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWBAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWBAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWBAttributeSet, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWBAttributeSet, Cooldown, COND_None, REPNOTIFY_Always);
}

void UWBAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWBAttributeSet, Health, OldHealth);
}

void UWBAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWBAttributeSet, MaxHealth, OldMaxHealth);
}

void UWBAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWBAttributeSet, Damage, OldDamage);
}

void UWBAttributeSet::OnRep_Cooldown(const FGameplayAttributeData& OldCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWBAttributeSet, Cooldown, OldCooldown);
}
