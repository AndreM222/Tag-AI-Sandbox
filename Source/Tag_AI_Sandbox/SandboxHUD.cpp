// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxHUD.h"

#include "AIStats.h"
#include "Engine/Engine.h"
#include "SMenuWidget.h"
#include "AIEntity/AI-Setup/AIEntityCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASandboxHUD::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Entities;
	FGeneralStats statsData;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEntityCharacter::StaticClass(), Entities);
	
	for (auto entity : Entities)
	{
		if (!statsData.Entities.Contains(entity->GetClass()->GetName()))
		{
			statsData.Entities.Add(entity->GetClass()->GetName());

		}

		statsData.Entities[entity->GetClass()->GetName()]++;
	}

	statsData.totalEntities = Entities.Num();
	statsData.totalTeams = statsData.Entities.Num();
	
	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SMenuWidget).OwningHud(this).Stats(statsData);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
	}
}