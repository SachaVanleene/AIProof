// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;


public class RoadToGPP : ModuleRules
{
	public RoadToGPP(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "GameplayTasks" });
	}
}
