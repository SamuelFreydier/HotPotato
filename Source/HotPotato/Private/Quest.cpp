// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "HotPotato/HotPotatoGameMode.h"

const TMap<EPotatoType, uint64> UQuestGenerator::PotatoValues = {
    {EPotatoType::POTATO, 10},
    {EPotatoType::CHIPS, 100},
    {EPotatoType::FRIES, 1000},
    {EPotatoType::POUTINE, 10000}
};

Quest::Quest()
{
}

Quest::~Quest()
{
}

void Quest::Tick( float DeltaSeconds )
{
    SecondsRemaining -= DeltaSeconds;
    
    if( SecondsRemaining <= 0.0 )
    {
        bHasBeenFailed = true;
    }
}

void Quest::AddObjective( const TSharedPtr<FFetchObjective>& Objective )
{
    if( Objective->GoalQuantity > 0 )
    {
        Objectives.push_back( Objective );
        Reward += Objective->Reward;
    }
}

void Quest::UpdateObjective( FPotatoDish& FetchedDish )
{
    bool bIsFinished = false;
    std::vector<TSharedPtr<FFetchObjective>>::iterator ObjectiveIterator = Objectives.begin();

    while( !bIsFinished && ObjectiveIterator != Objectives.end() )
    {
        TSharedPtr<FFetchObjective> CurrentObjective = ( *ObjectiveIterator );
        if( CurrentObjective->PotatoType == FetchedDish.GetType() )
        {
            uint16 QuantityCap = CurrentObjective->GoalQuantity - CurrentObjective->CurrentQuantity;
            uint16 QuantityTransfer = QuantityCap > FetchedDish.GetQuantity() ? FetchedDish.GetQuantity() : QuantityCap;
            CurrentObjective->CurrentQuantity += QuantityTransfer;
            FetchedDish.DecreaseQuantity( QuantityTransfer );
        }

        if( CurrentObjective->CurrentQuantity >= CurrentObjective->GoalQuantity )
        {
            ObjectiveIterator = Objectives.erase( ObjectiveIterator );
            bIsFinished = true;
        }
        else
        {
            ObjectiveIterator++;
        }
    }

    if( Objectives.empty() )
    {
        bIsCompleted = true;
    }
}

UQuestGenerator::UQuestGenerator()
{
}

UQuestGenerator::~UQuestGenerator()
{
}

TSharedPtr<Quest> UQuestGenerator::GenerateQuest( const uint64& ScoreSeed, const uint16& PotatoMaximum ) const
{
    TSharedPtr<Quest> NewQuest = MakeShared<Quest>();

    uint16 PotatoCpt = 0;
    
    for( const TPair<EPotatoType, uint64>& PotatoValuePair : PotatoValues )
    {
        uint16 PotatoNumber = ( ScoreSeed % ( PotatoValuePair.Value * 10 ) ) / PotatoValuePair.Value;

        if( PotatoNumber > PotatoCpt )
        {
            PotatoNumber = PotatoMaximum - PotatoCpt;
        }

        TSharedPtr<FFetchObjective> Objective = MakeShared<FFetchObjective>();
        Objective->PotatoType = PotatoValuePair.Key;
        Objective->GoalQuantity = PotatoNumber;
        Objective->Reward = PotatoNumber * PotatoValuePair.Value;

        NewQuest->AddObjective( Objective );

        PotatoCpt += PotatoNumber;
        if( PotatoCpt >= PotatoMaximum )
        {
            break;
        }
    }

    return NewQuest;
}
