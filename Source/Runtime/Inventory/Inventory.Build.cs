using UnrealBuildTool;

public class Inventory : ModuleRules
{
	public Inventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "CoreUObject",
            "Engine",
			"Items"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Inventory/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Inventory/Private"});
    }
}
