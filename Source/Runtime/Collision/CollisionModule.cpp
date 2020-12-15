#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
class FCollisionModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override { }
};

IMPLEMENT_MODULE(FCollisionModule, Collision)