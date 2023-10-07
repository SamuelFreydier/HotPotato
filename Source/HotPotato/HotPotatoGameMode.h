// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HotPotatoGameMode.generated.h"

UCLASS(minimalapi)
class AHotPotatoGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHotPotatoGameMode();

	const uint64& GetScore() const { return Score; }
	void IncrementScore( const uint64& Amount ) { Score += Amount; }
private:
	uint64 Score;
};



