// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Cell.h"
#include "Components/ArrowComponent.h"

// Sets default values
ALV_Cell::ALV_Cell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("USceneComponent"));
	RootComponent = mySceneComponent;

	myBottomArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("BottomArrowComponent"));
	myBottomArrowComponent->SetupAttachment(RootComponent);
	myBottomArrowComponent->SetRelativeLocation(FVector(0, 0, -50));

	myTopArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("TopArrowComponent"));
	myTopArrowComponent->SetupAttachment(RootComponent);
	myTopArrowComponent->SetRelativeLocation(FVector(0, 0, 50));

	myRightArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrowComponent"));
	myRightArrowComponent->SetupAttachment(RootComponent);
	myRightArrowComponent->SetRelativeLocation(FVector(0, 50, 0));
	myRightArrowComponent->Deactivate();

	myLeftArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrowComponent"));
	myLeftArrowComponent->SetupAttachment(RootComponent);
	myLeftArrowComponent->SetRelativeLocation(FVector(0, -50, 0));

	myLeftCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftCube"));
	myLeftCube->SetVisibility(true);
	myLeftCube->SetupAttachment(myLeftArrowComponent);

	myRightCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightCube"));
	myRightCube->SetVisibility(true);
	myRightCube->SetupAttachment(myRightArrowComponent);

	myTopCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopCube"));
	myTopCube->SetVisibility(true);
	myTopCube->SetupAttachment(myTopArrowComponent);

	myBottomCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomCube"));
	myBottomCube->SetVisibility(true);
	myBottomCube->SetupAttachment(myBottomArrowComponent);

}

// Called when the game starts or when spawned
void ALV_Cell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALV_Cell::GenerateLinks()
{
	if (myY > 0)
	{
		myHasBottomLink = FMath::RandBool();
	}
	if (myY < 2)
	{
		myHasTopLink = FMath::RandBool();
		
	}
	if (myX > 0)
	{
		myHasLeftLink = FMath::RandBool();
	}
	if (myX < 2)
	{
		myHasRightLink = FMath::RandBool();
	}

	if (myHasBottomLink) myNumberLinks++;
	if (myHasTopLink) myNumberLinks++;
	if (myHasLeftLink) myNumberLinks++;
	if (myHasRightLink) myNumberLinks++;
}

void ALV_Cell::ShowArrow()
{
	if (myHasBottomLink)
	{
		myBottomCube->SetVisibility(false);
	}
	if (myHasTopLink)
	{
		myTopCube->SetVisibility(false);
	}
	if (myHasRightLink)
	{
		myRightCube->SetVisibility(false);
	}
	if (myHasLeftLink)
	{
		myLeftCube->SetVisibility(false);
	}
}

void ALV_Cell::AddLinkRight()
{
	myHasRightLink = true;
}

void ALV_Cell::CheckNumberLinks()
{
	if (myNumberLinks >= 2)
		return;

	if (myHasRightLink)
	{
		int rand = FMath::RandRange(0, 1);
		if (rand == 0)
		{
			myHasTopLink = true;
		}
		else
		{
			myHasBottomLink = true;
		}
	}
	else
	{
		myHasRightLink = true;
	}
}