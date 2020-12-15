using UnrealBuildTool;

public class Interaction : ModuleRules
{
	public Interaction(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
			"Camera",
			"Collision",
            "CoreUObject",
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Interaction/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Interaction/Private"});
    }
}
