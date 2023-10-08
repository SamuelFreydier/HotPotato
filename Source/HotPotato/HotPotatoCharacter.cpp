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
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHotPotatoCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if( GEngine )
	{
		
		int key = 36;
		for( const auto& InventoryPair : Inventory )
		{
			GEngine->AddOnScreenDebugMessage(
				key,
				15.f,
				FColor::Yellow,
				FString::Printf( TEXT( "Nombre de %s : %d" ), *UEnum::GetValueAsName( InventoryPair.Key ).ToString(), InventoryPair.Value )
			);
			key++;

		}
		
	}
}

void AHotPotatoCharacter::GatherPotato( EPotatoType PotatoType, int32 Quantity )
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		15.f,
		FColor::Yellow,
		FString::Printf( TEXT( "Potato gathered" ) )
	);
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

	Inventory.Reset();
}
