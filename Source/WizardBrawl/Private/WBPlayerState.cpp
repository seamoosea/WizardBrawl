// Fill out your copyright notice in the Description page of Project Settings.

#include "WBPlayerState.h"


AWBPlayerState::AWBPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWBAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	Attributes = CreateDefaultSubobject<UWBAttributeSet>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* AWBPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UWBAttributeSet* AWBPlayerState::GetAttributeSet() const
{
	return Attributes;
}

void AWBPlayerState::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect) {
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid()) {
			FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}