#include "Runtime/UseFramework/Public/UseComponent.h"

#include "Runtime/UseFramework/Public/Events/UseEvents.h"

DEFINE_LOG_CATEGORY_STATIC(UseComponentLog, Log, Log)

UUseComponent::UUseComponent()
	: Listener()
	, GetUseTimeProvider(nullptr)
{

}

void UUseComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_CLIENT_CODE
	if (GetNetMode() != NM_DedicatedServer)
	{
		ClientRegisterEvents();
	}
#endif //WITH_CLIENT_CODE
}

void UUseComponent::ClientRegisterEvents()
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		TWeakObjectPtr<UUseComponent> WeakThis = this;
		
		Listener.Bind<FOnStartUse>([WeakThis](const FOnStartUse& InEvent)
		{
			if (UUseComponent* StrongThis = WeakThis.Get())
			{
				UE_LOG(UseComponentLog, Log, TEXT("Started using %s"), *StrongThis->GetOwner()->GetName());

				if (InEvent.UseTimeProvider != nullptr)
				{
					StrongThis->GetUseTimeProvider = InEvent.UseTimeProvider;
				}
			} 
		});

		Listener.Bind<FOnEndUse>([WeakThis](const FOnEndUse& InEvent)
		{
			if (UUseComponent* StrongThis = WeakThis.Get())
			{
				if (InEvent.UseDuration != 0.f)
				{
					UE_LOG(UseComponentLog, Log, TEXT("Stopped using %s after %f seconds"), *StrongThis->GetOwner()->GetName(), InEvent.UseDuration);
				}
				else
				{
					UE_LOG(UseComponentLog, Log, TEXT("Tapped"), *StrongThis->GetOwner()->GetName());
				}
			}
		});
	}
}
