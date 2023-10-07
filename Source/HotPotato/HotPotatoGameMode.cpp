// Copyright Epic Games, Inc. All Rights Reserved.

#include "HotPotatoGameMode.h"
#include "HotPotatoPlayerController.h"
#include "HotPotatoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHotPotatoGameMode::AHotPotatoGameMode()
	: Score( 0 )
{
	// use our custom PlayerController class
	PlayerControllerClass = AHotPotatoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
