#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FItemsModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FItemsModule, Items)