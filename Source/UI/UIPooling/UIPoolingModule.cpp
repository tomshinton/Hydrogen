#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FUIPoolingModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FUIPoolingModule, UIPooling)