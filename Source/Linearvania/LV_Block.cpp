// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Block.h"
#include "LV_Cell.h"

ALV_Block::ALV_Block()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ALV_Block::BeginPlay()
{
	Super::BeginPlay();

}

void ALV_Block::GenerateBlock(int aHeight, float aHeightSeparator, int aX)
{
	switch (myBlockType)
	{
	case BlockType::NORMAL:
	{
		for (int i = 0; i < aHeight; i++)
		{
			ALV_Cell* tile = GetWorld()->SpawnActor<ALV_Cell>(myTileTest, GetActorLocation() + FVector(0, 0, aHeightSeparator * i), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
			myCells.Add(tile);
			tile->myY = i;
			tile->myX = aX;
		}
		for (int i = 0; i < myCells.Num(); i++)
		{
			myCells[i]->GenerateLinks();
		}
		for (int i = 0; i < myCells.Num(); i++)
		{
			if (myCells[i]->myHasTopLink)
			{
				myCells[i + 1]->myHasBottomLink = true;
			}
			if (myCells[i]->myHasBottomLink)
			{
				myCells[i - 1]->myHasTopLink = true;
			}
		}
		break;
	}
	case BlockType::BOSS:
	{
		ALV_Cell* tile = GetWorld()->SpawnActor<ALV_Cell>(myTileTest, GetActorLocation() + FVector(0, 0, 0), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
		myCells.Add(tile);
		tile->myY = 0;
		tile->myX = aX;
		break;
	}
	default:
		break;
	}
}

void ALV_Block::CheckNeighbour(TArray<ALV_Block*> someBlocks, int anIndex)
{
	for (int i = 0; i < myCells.Num(); i++)
	{
		if (myCells[i]->myHasLeftLink)
		{
			someBlocks[anIndex - 1]->GetCell(i)->myHasRightLink = true;
		}
		if (myCells[i]->myHasRightLink && someBlocks.Num() > anIndex + 1)
		{
			someBlocks[anIndex + 1]->GetCell(i)->myHasLeftLink = true;
		}
	}
}

ALV_Cell* ALV_Block::GetCell(int anIndex)
{
	return myCells[anIndex];
}

void ALV_Block::ShowArrow()
{
	for (int i = 0; i < myCells.Num(); i++)
	{
		myCells[i]->ShowArrow();
	}
}

void ALV_Block::CheckLinks()
{
	int nbLinks = 0;
	for (int i = 0; i < myCells.Num(); i++)
	{
		myCells[i]->CheckNumberLinks();
		if (myCells[i]->myHasRightLink)
		{
			nbLinks++;
		}
	}
	if (nbLinks >= 2) return;

	while (nbLinks != 2)
	{
		int rand = FMath::RandRange(0, myCells.Num() - 1);
		if (!myCells[rand]->myHasRightLink)
		{
			myCells[rand]->AddLinkRight();
			nbLinks++;
		}
	}
}