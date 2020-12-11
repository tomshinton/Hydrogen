#pragma once

#include <Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h>

#include "HydrogenMovementComponent.generated.h"

class AController;

UCLASS(MinimalAPI)
class UHydrogenMovementComponent : public UCharacterMovementComponent 
{
	GENERATED_BODY()
public:

	UHydrogenMovementComponent(const FObjectInitializer& InObjectInitialiser);

#if WITH_CLIENT_CODE
	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
#endif //WITH_CLIENT_CODE

	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float TurnSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float SprintSpeed;

private:

	void MoveForward(const float InStrength);
	void MoveRight(const float InStrength);
	void TurnRight(const float InStrength);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Jump();
	bool Server_Jump_Validate() { return true; }

	void StartSprint();
	void StopSprint();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StartSprint();
	bool Server_StartSprint_Validate() { return true; }

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopSprint();
	bool Server_StopSprint_Validate() { return true; }

	float CachedWalkSpeed;
	TWeakObjectPtr<APlayerController> LocalPlayerController;
};
