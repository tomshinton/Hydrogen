#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FUIComponentsModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FUIComponentsModule, UIComponents)