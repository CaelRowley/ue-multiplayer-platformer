// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoopPlatformer : ModuleRules
{
	public CoopPlatformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
