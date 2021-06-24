// Fill out your copyright notice in the Description page of Project Settings.


#include "LV_LevelGenerator.h"

// Sets default values
ALV_LevelGenerator::ALV_LevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALV_LevelGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateLevel();
}

// Called every frame
void ALV_LevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALV_LevelGenerator::GenerateLevel()
{
	for (int i = 0; i < myLevelLength; i++)
	{
		for (int h = 0; h < myLevelHeight; h++)
		{
			AActor* tile = GetWorld()->SpawnActor<AActor>(myTileTest, GetActorLocation() + FVector(0, i * myLengthSeparator, h * myHeightSeparator), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
			mySpawnedTiles.Add(tile);
		}
	}
}