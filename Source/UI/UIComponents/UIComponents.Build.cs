using UnrealBuildTool;

public class UIComponents : ModuleRules
{
	public UIComponents(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject",
			"Inventory",
			"Items",
			"UIPooling",
			"UMG",
        });
		
		PublicIncludePaths.AddRange(new string[] {"UI/UIComponents/Public"});
		PrivateIncludePaths.AddRange(new string[] {"UI/UIComponents/Private"});
    }
}
