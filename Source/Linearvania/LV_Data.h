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

USTRUCT(BlueprintType)
struct FUpgradeToApply
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	FString myStatToApplyName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	float myValueToApply = 0;
};

USTRUCT(BlueprintType)
struct FUpgrade
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	FString myUpgradeName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	TArray<FUpgradeToApply> myUpgradesToApply;
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
