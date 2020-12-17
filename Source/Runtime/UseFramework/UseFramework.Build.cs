using UnrealBuildTool;

public class UseFramework : ModuleRules
{
	public UseFramework(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject",
			"ObjectMessaging"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/UseFramework/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/UseFramework/Private"});
    }
}
