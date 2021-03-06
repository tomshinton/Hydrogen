using UnrealBuildTool;

public class UICore : ModuleRules
{
	public UICore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "CoreUObject",
			"InputCore",
			"Inventory",
			"Items",
            "Engine",
			"SlateCore",
			"ObjectMessaging",
			"UIComponents",
			"UIPooling",
			"UMG"
        });
		
		PublicIncludePaths.AddRange(new string[] {"UI/UICore/Public"});
		PrivateIncludePaths.AddRange(new string[] {"UI/UICore/Private"});
    }
}
