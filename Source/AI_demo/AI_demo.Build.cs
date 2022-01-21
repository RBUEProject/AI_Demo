// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AI_demo : ModuleRules
{
	public AI_demo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "AIModule",
            "GameplayTasks",
            "NavigationSystem"
        });
	}
}
