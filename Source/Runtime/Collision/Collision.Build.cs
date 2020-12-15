using UnrealBuildTool;

public class Collision : ModuleRules
{
	public Collision(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Collision/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Collision/Private"});
    }
}
