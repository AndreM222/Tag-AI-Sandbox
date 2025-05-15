#pragma once

#include "AIStats.generated.h"

USTRUCT(BlueprintType)
struct FGeneralStats
{
	GENERATED_BODY()

	int totalEntities = 0;
	int totalTeams = 0;
	
	int generation = 0;

	TMap<FString, int32> Entities;
};