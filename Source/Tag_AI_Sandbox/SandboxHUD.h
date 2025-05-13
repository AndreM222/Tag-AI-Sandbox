// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SandboxHUD.generated.h"

/**
 * 
 */
UCLASS()
class TAG_AI_SANDBOX_API ASandboxHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<class SMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> WidgetContainer;

	virtual void BeginPlay() override;
};
