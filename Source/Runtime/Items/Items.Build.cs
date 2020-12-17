using UnrealBuildTool;

public class Items : ModuleRules
{
	public Items(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Items/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Items/Private"});
    }
}
