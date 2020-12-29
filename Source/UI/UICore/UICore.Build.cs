using UnrealBuildTool;

public class UICore : ModuleRules
{
	public UICore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject",
			"UIComponents",
			"UMG"
        });
		
		PublicIncludePaths.AddRange(new string[] {"UI/UICore/Public"});
		PrivateIncludePaths.AddRange(new string[] {"UI/UICore/Private"});
    }
}
