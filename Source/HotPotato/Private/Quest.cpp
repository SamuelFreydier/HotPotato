// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "HotPotato/HotPotatoGameMode.h"

const TMap<EPotatoType, uint64> QuestGenerator::PotatoValues = {
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

void Quest::UpdateObjective( EPotatoType PotatoType, int32& Quantity )
{
    bool bIsFinished = false;
    std::vector<TSharedPtr<FFetchObjective>>::iterator ObjectiveIterator = Objectives.begin();

    while( !bIsFinished && ObjectiveIterator != Objectives.end() )
    {
        TSharedPtr<FFetchObjective> CurrentObjective = ( *ObjectiveIterator );
        if( CurrentObjective->PotatoType == PotatoType )
        {
            uint16 QuantityCap = CurrentObjective->GoalQuantity - CurrentObjective->CurrentQuantity;
            uint16 QuantityTransfer = QuantityCap > Quantity ? Quantity : QuantityCap;
            CurrentObjective->CurrentQuantity += QuantityTransfer;
            Quantity -= QuantityTransfer;
            if( Quantity < 0 ) Quantity = 0;
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

void Quest::ShowQuest() const
{
    if( GEngine )
    {
        int32 indexdebug = 15;
        for( TSharedPtr<FFetchObjective> Objective : Objectives )
        {
            const TEnumAsByte<EPotatoType> PotatoEnum = Objective->PotatoType;
            FText PotatoTypeText;
            UEnum::GetDisplayValueAsText( PotatoEnum, PotatoTypeText );
            GEngine->AddOnScreenDebugMessage(
                indexdebug,
                1.f,
                FColor::Blue,
                FString::Printf( TEXT( "Fetch %d/%d %s" ), Objective->CurrentQuantity, Objective->GoalQuantity, *PotatoTypeText.ToString() )
            );
            indexdebug++;

        }
        GEngine->AddOnScreenDebugMessage(
            indexdebug,
            1.f,
            FColor::Blue,
            FString::Printf( TEXT( "Reward: %d" ), Reward )
        );
        GEngine->AddOnScreenDebugMessage(
            indexdebug + 1,
            1.f,
            FColor::Blue,
            FString::Printf( TEXT( "Remaining time: %f" ), SecondsRemaining )
        );
    }
}

QuestGenerator::QuestGenerator()
{
}

QuestGenerator::~QuestGenerator()
{
}

TSharedPtr<Quest> QuestGenerator::GenerateQuest( const uint64& ScoreSeed, const uint16& PotatoMaximum ) const
{
    TSharedPtr<Quest> NewQuest = MakeShared<Quest>();
    NewQuest->SetTimer( 40 );

    uint16 PotatoCpt = 0;
    
    for( const TPair<EPotatoType, uint64>& PotatoValuePair : PotatoValues )
    {
        uint16 PotatoNumber = ( ScoreSeed % ( PotatoValuePair.Value * 10 ) ) / PotatoValuePair.Value;

        if( PotatoNumber > PotatoMaximum - PotatoCpt )
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
