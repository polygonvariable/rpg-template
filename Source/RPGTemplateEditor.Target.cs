// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class RPGTemplateEditorTarget : TargetRules
{
	public RPGTemplateEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

        ExtraModuleNames.AddRange(new string[] { "RPGTemplate" });
        ExtraModuleNames.AddRange(
            new string[]
            {
                "RenShared",
                "RenWidget",
                "RenCore",
                "RenAsset",
                "RenStorage",
                "RenInventory",
                "RenEntity",
                "RenInteract"
            }
        );

    }
}
