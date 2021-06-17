// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Enemy.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ALV_Enemy::ALV_Enemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("USceneComponent"));
	RootComponent = mySceneComponent;

	mySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	mySpriteComponent->SetupAttachment(mySceneComponent);
}

// Called when the game starts or when spawned
void ALV_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALV_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

