// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Player.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSprite.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "LV_Bullet.h"

// Sets default values
ALV_Player::ALV_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mySpringArm->SetupAttachment(RootComponent);
	mySpringArm->TargetArmLength = 1000.f;

	// Setup the camera.
	myCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	myCameraComponent->SetupAttachment(mySpringArm);

	myFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipBook"));
	myFlipbookComponent->SetupAttachment(RootComponent);

	myShootPlace = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootPlace"));
	myShootPlace->SetupAttachment(myFlipbookComponent);

	FPlayerStatUpgrade fireRate = FPlayerStatUpgrade();
	fireRate.myName = "FireRate";
	fireRate.myBaseValue = 0.2f;
	fireRate.myCurrentValue = fireRate.myBaseValue;
	fireRate.myMinValue = 0.05f;
	myPlayerStatUpgrades.Add(fireRate);
}

// Called when the game starts or when spawned
void ALV_Player::BeginPlay()
{
	Super::BeginPlay();
	
	myShootRateIndex = GetPlayerUpgradeIndex("FireRate");

	myPlayerStatUpgrades[myShootRateIndex].myCurrentValue = myPlayerStatUpgrades[myShootRateIndex].myBaseValue;
}

// Called every frame
void ALV_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(myIsShooting && myCanShoot)
	{
		SpawnBullet();
	}

	if (!myCanShoot)
	{
		myCurrentShootTime += DeltaTime;
		if (myCurrentShootTime >= myPlayerStatUpgrades[myShootRateIndex].myCurrentValue)
		{
			myCurrentShootTime = 0;
			myCanShoot = true;
		}
	}

	if (myFlipbookComponent != nullptr)
	{
		if (myIsShooting)
		{
			if (myFlipbookComponent != nullptr && GetMovementComponent()->Velocity.Z != 0)
			{
				myFlipbookComponent->SetFlipbook(myJumpShootFlipbook);
			}
			else if (myFlipbookComponent != nullptr)
			{
				myFlipbookComponent->SetFlipbook(myShootFlipbook);
			}
		}
		else
		{
			if (GetMovementComponent()->Velocity.Y == 0)
			{
				myFlipbookComponent->SetFlipbook(myIdleFlipbook);
			}
			else if (GetMovementComponent()->Velocity.Z == 0)
			{
				myFlipbookComponent->SetFlipbook(myRunFlipbook);
			}
			else
			{
				myFlipbookComponent->SetFlipbook(myJumpFlipbook);
			}
		}
	}

}

// Called to bind functionality to input
void ALV_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Right", this, &ALV_Player::Right);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ALV_Player::PlayerJump);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ALV_Player::Shoot);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &ALV_Player::StopShoot);

}

void ALV_Player::Right(float aValue)
{
	if (aValue != 0.0f && Controller != NULL)
	{
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, aValue);

		if (myFlipbookComponent != nullptr && GetMovementComponent()->Velocity.Y > 0)
		{
			myFlipbookComponent->SetRelativeRotation(FRotator(0, 90, 0));
		}
		else if(myFlipbookComponent != nullptr)
		{
			myFlipbookComponent->SetRelativeRotation(FRotator(0, -90, 0));
		}
	}
}

void ALV_Player::PlayerJump()
{
	Jump();
}

void ALV_Player::PlayerStopJump()
{
	StopJumping();
}

void ALV_Player::Shoot()
{
	myIsShooting = true;
}

void ALV_Player::StopShoot()
{
	myIsShooting = false;
}

void ALV_Player::SpawnBullet()
{
	ALV_Bullet* bullet = GetWorld()->SpawnActor<ALV_Bullet>(myBulletBP, myShootPlace->GetComponentLocation(), FRotator(0.0f, 0.f, 0.f), FActorSpawnParameters());
	if (bullet != nullptr)
	{
		bullet->myDirection = myShootPlace->GetForwardVector();
	}
	myCurrentShootTime = 0;
	myCanShoot = false;
}

void ALV_Player::AddBonus(const FString& aName, float aValue)
{
	for (int i = 0; i < myPlayerStatUpgrades.Num(); i++)
	{
		if (myPlayerStatUpgrades[i].myName == aName)
		{
			myPlayerStatUpgrades[i].myBonusValue += aValue;
			myPlayerStatUpgrades[i].myCurrentValue = myPlayerStatUpgrades[i].myBaseValue - myPlayerStatUpgrades[i].myBaseValue * myPlayerStatUpgrades[i].myBonusValue;
			if (myPlayerStatUpgrades[i].myCurrentValue < myPlayerStatUpgrades[i].myMinValue)
			{
				myPlayerStatUpgrades[i].myCurrentValue = myPlayerStatUpgrades[i].myMinValue;
			}
			return;
		}
	}
}

int ALV_Player::GetPlayerUpgradeIndex(const FString& aName)
{
	for (int i = 0; i < myPlayerStatUpgrades.Num(); i++)
	{
		if (myPlayerStatUpgrades[i].myName == aName)
		{
			return i;
		}
	}

	return -1;
}