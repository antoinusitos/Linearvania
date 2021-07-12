// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Bullet.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "LV_Enemy.h"

// Sets default values
ALV_Bullet::ALV_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("USceneComponent"));
	RootComponent = mySceneComponent;

	mySpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	mySpriteComponent->SetupAttachment(mySceneComponent);

	myCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	myCollisionComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALV_Bullet::BeginPlay()
{
	Super::BeginPlay();

	myCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ALV_Bullet::OnOverlapBegin);
	myCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ALV_Bullet::OnOverlapEnd);
	
	myStartPos = GetActorLocation();
}

// Called every frame
void ALV_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(myDirection * mySpeed + FVector::UpVector * myBaseGravity);

	if (!myGravityApplied && FVector::Dist(myStartPos, GetActorLocation()) >= myRange)
	{
		myGravityApplied = true;
		myBaseGravity = -9;
	}
}

void ALV_Bullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ALV_Enemy* enemy = Cast<ALV_Enemy>(OtherActor);
		if (enemy != nullptr)
		{
			enemy->myLife -= myDamage;
			if (enemy->myLife <= 0)
			{
				enemy->Destroy();
			}
			Destroy();
		}
	}
}

void ALV_Bullet::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}