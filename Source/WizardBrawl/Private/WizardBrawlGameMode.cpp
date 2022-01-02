// Copyright Epic Games, Inc. All Rights Reserved.

#include "WizardBrawlGameMode.h"
#include "WizardBrawlPlayerController.h"
#include "WizardBrawlCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWizardBrawlGameMode::AWizardBrawlGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWizardBrawlPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/WizardBrawl/Blueprints/BP_WizardBrawlCharacter.BP_WizardBrawlCharacter_C"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
