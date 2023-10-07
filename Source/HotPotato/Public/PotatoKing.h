// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotatoDish.h"
#include "Quest.h"
#include "HotPotato/HotPotatoGameMode.h"
#include "PotatoKing.generated.h"

UCLASS(Blueprintable)
class HOTPOTATO_API APotatoKing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotatoKing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void PotatoBeginPlay();

	UFUNCTION(BlueprintCallable)
	void Init( int32 BaseGluttony = 5, int32 BaseScoreOffset = 30 );

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Eat some kind of potato (yes it is cannibalism)
	void EatPotato( EPotatoType BasePotato, int32& Quantity );

	void AddQuest( int32 ScoreOffset = 0 );

private:
	std::vector<TSharedPtr<Quest>> Quests;

	UPROPERTY( EditAnywhere )
	int32 PotatoGluttony{ 5 };

	// Référence vers le GameMode
	AHotPotatoGameMode* GameMode;

};
