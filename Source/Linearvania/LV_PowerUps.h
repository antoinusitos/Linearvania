// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LV_Data.h"
#include "LV_PowerUps.generated.h"

/**
 * 
 */
UCLASS()
class LINEARVANIA_API ULV_PowerUps : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	TArray<FPowerUp> myPowerUps;
	
};
