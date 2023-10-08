// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EPotatoType : uint8
{
	POTATO UMETA( DisplayName = "Potato" ),
	CHIPS UMETA( DisplayName = "Chips" ),
	FRIES UMETA( DisplayName = "Fries" ),
	POUTINE UMETA( DisplayName = "Poutine" )
};

/**
 * 
 */
class HOTPOTATO_API FPotatoDish
{
public:
	FPotatoDish();
	~FPotatoDish();

	const EPotatoType& GetType() const { return PotatoType; }
	const int& GetQuantity() const { return Quantity; }
	void DecreaseQuantity( const int& Amount );

private:
	EPotatoType PotatoType;
	int Quantity;
};
