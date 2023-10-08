// Copyright Epic Games, Inc. All Rights Reserved.

#include "HotPotatoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AHotPotatoCharacter::AHotPotatoCharacter()
	: ACharacter()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHotPotatoCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AHotPotatoCharacter::GatherPotato( EPotatoType PotatoType, int32 Quantity )
{
	if( Inventory.Contains( PotatoType ) )
	{
		Inventory[ PotatoType ] += Quantity;
	}
	else
	{
		Inventory.Add( PotatoType, Quantity );
	}
}

void AHotPotatoCharacter::GivePotatoes( APotatoKing* PotatoKing )
{
	for( TPair<EPotatoType, int32>& InventoryPair : Inventory )
	{
		PotatoKing->EatPotato( InventoryPair.Key, InventoryPair.Value );
	}
}

FString AHotPotatoCharacter::InventoryToString() const
{
	FStringBuilderBase InventoryStringBuilder;

	for( const auto& InventoryPair : Inventory )
	{
		const TEnumAsByte<EPotatoType> PotatoEnum = InventoryPair.Key;
		FText PotatoTypeText;
		UEnum::GetDisplayValueAsText( PotatoEnum, PotatoTypeText );

		InventoryStringBuilder.Append( FString::Printf( TEXT( "%s : %d\n" ), *PotatoTypeText.ToString(), InventoryPair.Value ) );
	}

	return InventoryStringBuilder.ToString();
}
