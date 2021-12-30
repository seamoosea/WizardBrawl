// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WizardBrawl : ModuleRules
{
	public WizardBrawl(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "GamePlayAbilities", "GameplayTags", "AIModule", "GameplayTasks", "NavigationSystem" });
    }
}
