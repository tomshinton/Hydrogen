#include <Runtime/Core/Public/Modules/ModuleManager.h>
 
struct FTestType;

class FMovementModule : public IModuleInterface
{
	virtual void StartupModule() override { }
	virtual void ShutdownModule() override 
	{
	}
};

IMPLEMENT_MODULE(FMovementModule, Movement)