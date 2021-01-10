using UnrealBuildTool;

public class UIPooling : ModuleRules
{
	public UIPooling(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "CoreUObject",
            "Engine",
			"UMG"
        });
		
		PublicIncludePaths.AddRange(new string[] {"UI/UIPooling/Public"});
		PrivateIncludePaths.AddRange(new string[] {"UI/UIPooling/Private"});

        PublicDefinitions.Add("UIPOOLING=1");
    }
}
