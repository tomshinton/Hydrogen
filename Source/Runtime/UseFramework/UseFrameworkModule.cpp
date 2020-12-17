#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FUseFrameworkModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FUseFrameworkModule, UseFramework)