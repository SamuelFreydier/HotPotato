// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PotatoDish.h"
#include "Quest.generated.h"


USTRUCT()
struct FFetchObjective : public FTableRowBase
{ 
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere )
	EPotatoType PotatoType;

	UPROPERTY( EditAnywhere )
	uint16 GoalQuantity;

	UPROPERTY( EditAnywhere )
	uint16 CurrentQuantity = 0;

	UPROPERTY( EditAnywhere )
	uint64 Reward = 0;
};

/**
 * 
 */
class HOTPOTATO_API Quest
{
public:
	Quest();
	~Quest();

	void Tick( float DeltaSeconds );

	void AddObjective( const TSharedPtr<FFetchObjective>& Objective );
	void UpdateObjective( EPotatoType PotatoType, int32& Quantity );

	bool IsQuestCompleted() const { return bIsCompleted; }
	bool HasBeenFailed() const { return bHasBeenFailed; }
	const std::vector<TSharedPtr<FFetchObjective>>& GetObjectives() const { return Objectives; }
	const uint64& GetReward() const { return Reward; }
	void SetTimer( const float& Seconds ) { SecondsRemaining = Seconds; }
	const float& GetSecondsRemaining() const { return SecondsRemaining; }

	void ShowQuest() const;


private:
	std::vector<TSharedPtr<FFetchObjective>> Objectives;
	float SecondsRemaining;
	uint64 Reward = 0;

	bool bIsCompleted = false;
	bool bHasBeenFailed = false;
};


class HOTPOTATO_API QuestGenerator
{
public:
	QuestGenerator();
	~QuestGenerator();

	TSharedPtr<Quest> GenerateQuest( const uint64& ScoreSeed, const uint16& PotatoMaximum ) const;

private:
	static const TMap<EPotatoType, uint64> PotatoValues;
};