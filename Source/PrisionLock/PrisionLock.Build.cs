// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PrisionLock : ModuleRules
{
	public PrisionLock(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
