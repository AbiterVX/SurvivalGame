// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsClientTarget : TargetRules
{
	public SurvivorsClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SurvivorsClient");
		ExtraModuleNames.Add("Tools");
		ExtraModuleNames.Add("Nature");
		ExtraModuleNames.Add("WorldItem");
	}
}
