// Hydrogen 2020

#include "UI/UIComponents/Public/Debug/UI_Watermark.h"

#include <Runtime/UMG/Public/Components/TextBlock.h>

namespace ProjectConfigKeys
{
	const FString ProjectName = TEXT("ProjectName");
	const FString ProjectVersion = TEXT("ProjectVersion");

	const FString DefaultGameIni = TEXT("/Script/EngineSettings.GeneralProjectSettings");
}

UUI_Watermark::UUI_Watermark(const FObjectInitializer& InObjectInialiser)
	: Super(InObjectInialiser)
	, ProjectNameText(nullptr)
	, ProjectVersionText(nullptr)
{

}

void UUI_Watermark::NativeConstruct()
{
	Super::NativeConstruct();

	if (ProjectVersionText != nullptr)
	{
		FString AppVersion;
		GConfig->GetString(
			*ProjectConfigKeys::DefaultGameIni,
			*ProjectConfigKeys::ProjectVersion,
			AppVersion,
			GGameIni);

		ProjectVersionText->SetText(FText::FromString(AppVersion));
	}

	if (ProjectNameText != nullptr)
	{
		FString ProjectName;
		GConfig->GetString(
			*ProjectConfigKeys::DefaultGameIni,
			*ProjectConfigKeys::ProjectName,
			ProjectName,
			GGameIni);

		ProjectNameText->SetText(FText::FromString(ProjectName));
	}
}
