// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoDish.h"

FPotatoDish::FPotatoDish()
{
}

FPotatoDish::~FPotatoDish()
{
}

void FPotatoDish::DecreaseQuantity( const int& Amount )
{
    Quantity -= Amount;

    if( Quantity < 0 )
    {
        Quantity = 0;
    }
}
