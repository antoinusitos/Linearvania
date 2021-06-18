// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_PowerUp.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "LV_Player.h"

// Sets default values
ALV_PowerUp::ALV_PowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("USceneComponent"));
	RootComponent = mySceneComponent;

	mySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	mySpriteComponent->SetupAttachment(RootComponent);

	myCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	myCollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALV_PowerUp::BeginPlay()
{
	Super::BeginPlay();

	myCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALV_PowerUp::OnOverlapBegin);
	myCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ALV_PowerUp::OnOverlapEnd);

}

// Called every frame
void ALV_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALV_PowerUp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ALV_Player* player = Cast<ALV_Player>(OtherActor);
		if (player != nullptr)
		{
			player->AddBonus(myBonusName, myBonusPercent);
			Destroy();
		}
	}
}

void ALV_PowerUp::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}