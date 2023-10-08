// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoKing.h"
#include <iostream>

APotatoKing::APotatoKing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APotatoKing::BeginPlay()
{
	Super::BeginPlay();
}

void APotatoKing::PotatoBeginPlay()
{
	UWorld* World = GetWorld();
	if( World )
	{
		GameMode = ( AHotPotatoGameMode* ) World->GetAuthGameMode();
	}
}

void APotatoKing::Init( int32 BaseGluttony, int32 BaseScoreOffset )
{
	PotatoGluttony = BaseGluttony;

	if( GameMode )
	{
		AddQuest( BaseScoreOffset );
	}
}

// Called every frame
void APotatoKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( GameMode && GEngine )
	{
		GEngine->AddOnScreenDebugMessage(
			2,
			15.f,
			FColor::Green,
			FString::Printf( TEXT( "Score: %d" ), GameMode->GetScore() )
		);
	}

	// Tick des quêtes existantes
	for( TSharedPtr<Quest>& Quest : Quests )
	{
		Quest->Tick( DeltaTime );

		if( Quest->HasBeenFailed() )
		{
			// Condition de défaite
			if( GEngine )
			{
				GEngine->AddOnScreenDebugMessage(
					50,
					15.f,
					FColor::Red,
					FString::Printf( TEXT( "Vous avez perdu bande de gros nazes !" ) )
				);
			}
		}

		Quest->ShowQuest();
	}
}

void APotatoKing::EatPotato( EPotatoType BasePotato, int32& Quantity )
{
	bool bIsFinished = false;
	std::vector<TSharedPtr<Quest>>::iterator QuestIterator = Quests.begin();

	while( !bIsFinished && QuestIterator != Quests.end() )
	{
		TSharedPtr<Quest> CurrentQuest = ( *QuestIterator );

		CurrentQuest->UpdateObjective( BasePotato, Quantity );

		if( CurrentQuest->IsQuestCompleted() )
		{
			QuestIterator = Quests.erase( QuestIterator );
			GameMode->IncrementScore( CurrentQuest->GetReward() );

			// Le roi a toujours faim hein tu croyais quoi
			PotatoGluttony++;
			AddQuest();
		}
		else
		{
			QuestIterator++;
		}

		if( Quantity <= 0 )
		{
			bIsFinished = true;
		}
	}
}

void APotatoKing::AddQuest( int32 BaseScoreOffset )
{
	QuestGenerator QuestGenerator;

	TSharedPtr<Quest> NewQuest = QuestGenerator.GenerateQuest( GameMode->GetScore() + BaseScoreOffset, PotatoGluttony );

	if( !NewQuest->GetObjectives().empty() )
	{
		Quests.push_back( NewQuest );
	}
}

