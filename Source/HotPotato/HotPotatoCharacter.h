// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HotPotato/Public/PotatoDish.h"
#include "HotPotato/Public/PotatoKing.h"
#include "HotPotatoCharacter.generated.h"

UCLASS(Blueprintable)
class AHotPotatoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHotPotatoCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable)
	void GatherPotato( EPotatoType PotatoType, int32 Quantity = 1 );

	UFUNCTION(BlueprintCallable)
	void GivePotatoes( APotatoKing* PotatoKing );

	UFUNCTION(BlueprintCallable)
	FString InventoryToString() const;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	TMap<EPotatoType, int32> Inventory;
};

