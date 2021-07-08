// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_LevelGenerator.h"
#include "LV_Block.h"

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
		ALV_Block* tile = GetWorld()->SpawnActor<ALV_Block>(myTileTest, GetActorLocation() + FVector(0, i * myLengthSeparator, 0), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
		mySpawnedTiles.Add(tile);
		tile->GenerateBlock(myLevelHeight, myHeightSeparator, i);
	}
	for (int i = 0; i < mySpawnedTiles.Num() - 1; i++)
	{
		mySpawnedTiles[i]->CheckLinks();
		mySpawnedTiles[i]->CheckNeighbour(mySpawnedTiles, i);
	}
	for (int i = 0; i < mySpawnedTiles.Num(); i++)
	{
		mySpawnedTiles[i]->ShowArrow();
	}
}