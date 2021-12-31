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
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/WizardBrawlBPs/Blueprints/BP_WizardBrawlCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}