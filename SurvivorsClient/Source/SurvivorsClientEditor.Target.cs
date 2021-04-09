// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SurvivorsClientEditorTarget : TargetRules
{
	public SurvivorsClientEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SurvivorsClient");
		ExtraModuleNames.Add("Tools");
		ExtraModuleNames.Add("Nature");
		ExtraModuleNames.Add("WorldItem");
		
	}
}
