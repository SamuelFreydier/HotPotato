#include "BasePotato.h"

// Définit les valeurs par défaut
ABasePotato::ABasePotato()
{
	// Définissez ce empty pour appeler Tick() à chaque frame. Vous pouvez désactiver cette option pour améliorer les performances si vous n’en avez pas besoin.
	PrimaryActorTick.bCanEverTick = true;
}

// Appelé au début du jeu ou au moment de l'apparition de l'animal.
void ABasePotato::BeginPlay()
{
	Super::BeginPlay();
}

// Appelé chaque frame
void ABasePotato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Appelé pour lier la fonctionnalité à l’entrée
void ABasePotato::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
