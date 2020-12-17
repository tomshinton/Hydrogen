// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Hydrogen : ModuleRules
{
	public Hydrogen(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
"Items",
"Inventory",
"UseFramework",
            "Collision",
            "Interaction",
            "Camera",
            "Movement"
		});

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "ObjectMessaging"
        });
    }
}
