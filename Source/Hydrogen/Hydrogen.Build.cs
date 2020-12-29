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
            "Camera",
            "Collision",
            "Interaction",
            "Inventory",
            "Items",
            "Movement",
            "UICore",
			"UseFramework",
		});

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "ObjectMessaging"
        });
    }
}
