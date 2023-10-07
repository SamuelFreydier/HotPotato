#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePotato.generated.h"

UCLASS()
class HOTPOTATO_API ABasePotato : public ACharacter
{
	GENERATED_BODY()

public:
	// Définit les valeurs par défaut des propriétés de ce empty
	ABasePotato();

protected:
	// Appelé au début du jeu ou au moment de l'apparition de l'animal.
	virtual void BeginPlay() override;

public:
	// Appelé chaque frame
	virtual void Tick(float DeltaTime) override;

	// Appelé pour lier la fonctionnalité à l’entrée
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
