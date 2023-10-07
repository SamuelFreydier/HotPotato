// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HotPotatoGameMode.generated.h"

UCLASS(minimalapi)
class AHotPotatoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AHotPotatoGameMode();

	const uint64& GetScore() const { return Score; }
	void IncrementScore( const uint64& Amount ) { Score += Amount; }
private:
	uint64 Score;
};



