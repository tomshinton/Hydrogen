#include <Runtime/Movement/Public/HydrogenMovementComponent.h>

#include <Runtime/Engine/Classes/GameFramework/Pawn.h>

DEFINE_LOG_CATEGORY_STATIC(HyrogenMovementComponent, Log, Log)

namespace MovementComponentBindings
{
	const FName MoveForwardBinding = TEXT("MoveForward");
	const FName MoveRightBinding = TEXT("MoveRight");
	const FName TurnRightBinding = TEXT("TurnRight");

	const FName JumpBinding = TEXT("Jump");
	const FName ToggleSprintBinding = TEXT("ToggleSprint");
}

UHydrogenMovementComponent::UHydrogenMovementComponent(const FObjectInitializer& InObjectInitialiser)
	: Super(InObjectInitialiser)
	, TurnSpeed(10.f)
	, CachedWalkSpeed(MaxWalkSpeed)
	, LocalPlayerController()
{

}

void UHydrogenMovementComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_CLIENT_CODE
	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		if (APawn* OwningPawn = GetOwner<APawn>())
		{
			if (APlayerController* LocalController = OwningPawn->GetController<APlayerController>())
			{
				LocalPlayerController = LocalController;
			}
			else
			{
				OwningPawn->OnPossess.AddWeakLambda(this, [this](const AController& InController)
				{
					if (const APlayerController* Controller = Cast<APlayerController>(&InController))
					{
						LocalPlayerController = const_cast<APlayerController*>(Controller);
					}
				});
			}
		}
	}
#endif //WITH_CLIENT_CODE
}

#if WITH_CLIENT_CODE
void UHydrogenMovementComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	Super::SetupComponentInputBindings(PlayerInputComponent);
	
	PlayerInputComponent.BindAxis(MovementComponentBindings::MoveForwardBinding, this, &UHydrogenMovementComponent::MoveForward);
	PlayerInputComponent.BindAxis(MovementComponentBindings::MoveRightBinding, this, &UHydrogenMovementComponent::MoveRight);
	PlayerInputComponent.BindAxis(MovementComponentBindings::TurnRightBinding, this, &UHydrogenMovementComponent::TurnRight);

	PlayerInputComponent.BindAction(MovementComponentBindings::JumpBinding, IE_Pressed, this, &UHydrogenMovementComponent::Server_Jump);

	PlayerInputComponent.BindAction(MovementComponentBindings::ToggleSprintBinding, IE_Pressed, this, &UHydrogenMovementComponent::StartSprint);
	PlayerInputComponent.BindAction(MovementComponentBindings::ToggleSprintBinding, IE_Released, this, &UHydrogenMovementComponent::StopSprint);
}
#endif //WITH_CLIENT_CODE

void UHydrogenMovementComponent::MoveForward(const float InStrength)
{
	if (!FMath::IsNearlyZero(InStrength))
	{
		AddInputVector(GetOwner()->GetActorForwardVector() * InStrength, false);
	}
}

void UHydrogenMovementComponent::MoveRight(const float InStrength)
{
	if (!FMath::IsNearlyZero(InStrength))
	{
		AddInputVector(GetOwner()->GetActorRightVector() * InStrength, false);
	}
}

void UHydrogenMovementComponent::TurnRight(const float InStrength)
{
	if (!FMath::IsNearlyZero(InStrength) && LocalPlayerController.IsValid())
	{
		LocalPlayerController->AddYawInput(InStrength * TurnSpeed);
	}
}

void UHydrogenMovementComponent::Server_Jump_Implementation()
{
	DoJump(false);
}

void UHydrogenMovementComponent::StartSprint()
{
	MaxWalkSpeed = SprintSpeed;
	Server_StartSprint();
}

void UHydrogenMovementComponent::StopSprint()
{
	MaxWalkSpeed = CachedWalkSpeed;
	Server_StopSprint();
}

void UHydrogenMovementComponent::Server_StartSprint_Implementation()
{
	MaxWalkSpeed = SprintSpeed;
}

void UHydrogenMovementComponent::Server_StopSprint_Implementation()
{
	MaxWalkSpeed = CachedWalkSpeed;
}

