// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWizardBrawl, Log, All);

UENUM(BlueprintType)
enum class EWBAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Blink,
	Push,
	Wall,
	Boomerang,
};
