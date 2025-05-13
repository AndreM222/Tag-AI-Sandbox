// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxHUD.h"
#include "Engine/Engine.h"
#include "SMenuWidget.h"
#include "AIEntity/AI-Setup/AIEntityCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASandboxHUD::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Entities;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEntityCharacter::StaticClass(), Entities);

	int32 totalPawns = Entities.Num();


	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SMenuWidget).OwningHud(this).TotalPawns(totalPawns);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
	}
}
