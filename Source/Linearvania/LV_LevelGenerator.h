// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LV_LevelGenerator.generated.h"

class ALV_Block;

UCLASS()
class LINEARVANIA_API ALV_LevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALV_LevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	TSubclassOf<ALV_Block> myTileTest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	int myLevelLength = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	int myLevelHeight = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	float myHeightSeparator = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	float myLengthSeparator = 1;

private:
	TArray<ALV_Block*> mySpawnedTiles;

public:
	void GenerateLevel();

};
