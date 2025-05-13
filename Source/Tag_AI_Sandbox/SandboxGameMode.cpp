// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxGameMode.h"

#include "SandboxHUD.h"

ASandboxGameMode::ASandboxGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/AI-Entities/BP_UserCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = ASandboxHUD::StaticClass();
}
