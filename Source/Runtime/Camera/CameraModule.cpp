#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FCameraModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FCameraModule, Camera)