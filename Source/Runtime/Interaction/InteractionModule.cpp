#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FInteractionModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FInteractionModule, Interaction)