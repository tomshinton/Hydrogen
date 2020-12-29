#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FUICoreModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FUICoreModule, UICore)