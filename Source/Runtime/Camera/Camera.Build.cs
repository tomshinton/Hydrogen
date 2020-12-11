using UnrealBuildTool;

public class Camera : ModuleRules
{
	public Camera(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

        PrivateDependencyModuleNames.AddRange(new string[] 
        {
            "Engine",
            "CoreUObject"
        });
		
		PublicIncludePaths.AddRange(new string[] {"Runtime/Camera/Public"});
		PrivateIncludePaths.AddRange(new string[] {"Runtime/Camera/Private"});
    }
}
