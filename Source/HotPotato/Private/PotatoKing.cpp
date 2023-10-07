// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoKing.h"

APotatoKing::APotatoKing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GameMode = ( AHotPotatoGameMode* ) GetWorld()->GetAuthGameMode();
}

// Called when the game starts or when spawned
void APotatoKing::BeginPlay()
{
	Super::BeginPlay();
	
	AddQuest();
}

void APotatoKing::Init( const uint16& BaseGluttony )
{
	PotatoGluttony = BaseGluttony;
}

// Called every frame
void APotatoKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
					-1,
					15.f,
					FColor::Red,
					FString::Printf( TEXT( "Vous avez perdu bande de gros nazes !" ) )
				);
			}
		}
	}
}

void APotatoKing::EatPotato( FPotatoDish& PotatoDish )
{
	bool bIsFinished = false;
	uint64 Reward = 0;
	std::vector<TSharedPtr<Quest>>::iterator QuestIterator = Quests.begin();

	while( !bIsFinished && QuestIterator != Quests.end() )
	{
		TSharedPtr<Quest> CurrentQuest = ( *QuestIterator );

		CurrentQuest->UpdateObjective( PotatoDish );

		if( CurrentQuest->IsQuestCompleted() )
		{
			Reward += CurrentQuest->GetReward();
			QuestIterator = Quests.erase( QuestIterator );

			// Le roi a toujours faim hein tu croyais quoi
			PotatoGluttony++;
			AddQuest();
		}
		else
		{
			QuestIterator++;
		}

		if( PotatoDish.GetQuantity() <= 0 )
		{
			bIsFinished = true;
		}
	}

	GameMode->IncrementScore( Reward );
}

void APotatoKing::AddQuest()
{
	UQuestGenerator QuestGenerator;

	TSharedPtr<Quest> NewQuest = QuestGenerator.GenerateQuest( GameMode->GetScore(), PotatoGluttony );

	if( !NewQuest->GetObjectives().empty() )
	{
		Quests.push_back( NewQuest );
	}
}

