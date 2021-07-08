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

UENUM(BlueprintType)
enum class PowerUpReceiver : uint8 {
	PLAYER = 0 UMETA(DisplayName = "PLAYER"),
	BULLET = 1  UMETA(DisplayName = "BULLET"),
	WORLD = 2  UMETA(DisplayName = "WORLD"),
};

USTRUCT(BlueprintType)
struct FPowerUp
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	FString myPowerUpName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	int myID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	PowerUpReceiver myReceiver;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	FString myVariableToChange = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	float myPercentageToApply = 0;
};



UENUM(BlueprintType)
enum class BlockType : uint8 {
	BOSS = 0 UMETA(DisplayName = "BOSS"),
	NORMAL = 1  UMETA(DisplayName = "NORMAL"),
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
