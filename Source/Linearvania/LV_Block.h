// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LV_Data.h"
#include "LV_Block.generated.h"

class ALV_Cell;

/**
 * 
 */
UCLASS()
class LINEARVANIA_API ALV_Block : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALV_Block();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	BlockType myBlockType = BlockType::NORMAL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	TArray<ALV_Cell*> myCells;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	TSubclassOf<ALV_Cell> myTileTest;

public:
	void GenerateBlock(int aHeight, float aHeightSeparator, int aX);

	void CheckNeighbour(TArray<ALV_Block*> someBlocks, int anIndex);

	ALV_Cell* GetCell(int anIndex);

	void ShowArrow();

	void CheckLinks();
};
