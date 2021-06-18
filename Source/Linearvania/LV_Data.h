// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LV_Data.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStatUpgrade
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
		FString myName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
		float myBaseValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
		float myCurrentValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
		float myMinValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
		float myBonusValue = 0;
};

/**
 * 
 */
class LINEARVANIA_API LV_Data
{
public:
	LV_Data();
	~LV_Data();
};
