// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HotPotato/Public/PotatoDish.h"
#include "HotPotato/Public/PotatoKing.h"
#include "HotPotatoCharacter.generated.h"

UCLASS(Blueprintable)
class AHotPotatoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHotPotatoCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void GatherPotato( EPotatoType PotatoType, int32 Quantity = 1 );

	UFUNCTION(BlueprintCallable)
	void GivePotatoes( APotatoKing* PotatoKing );

	UFUNCTION(BlueprintCallable)
	FString InventoryToString() const;

private:
	TMap<EPotatoType, int32> Inventory;
};

