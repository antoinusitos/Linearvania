// Fill out your copyright notice in the Description page of Project Settings.

#include "LV_Player.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperSprite.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "LV_Bullet.h"
#include "LV_DataAsset.h"

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
}

// Called when the game starts or when spawned
void ALV_Player::BeginPlay()
{
	Super::BeginPlay();
	
	LoadUpgrades();

	UCharacterMovementComponent* movementComp = GetCharacterMovement();
	if (movementComp != nullptr && myMovementSpeedIndex != -1)
	{
		movementComp->MaxWalkSpeed = myPlayerStatUpgrades[myMovementSpeedIndex].myCurrentValue;
	}

	if (myHealthIndex != -1)
	{
		myCurrentHealth = myPlayerStatUpgrades[myHealthIndex].myCurrentValue;
	}
	
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
		if (myPrimaryFireRateIndex != -1 && myCurrentShootTime >= myPlayerStatUpgrades[myPrimaryFireRateIndex].myCurrentValue)
		{
			myCurrentShootTime = 0;
			myCanShoot = true;
		}
	}

	if (myFlipbookComponent != nullptr)
	{
		if (GetMovementComponent()->Velocity.Z != 0)
		{
			myFlipbookComponent->SetFlipbook(myJumpFlipbook);
		}
		else if (GetMovementComponent()->Velocity.Y != 0)
		{
			myFlipbookComponent->SetFlipbook(myRunFlipbook);
		}
		else
		{
			myFlipbookComponent->SetFlipbook(myIdleFlipbook);
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

		if (myFlipbookComponent != nullptr && aValue > 0)
		{
			myFlipbookComponent->SetRelativeRotation(FRotator(0, 90, 0));
		}
		else if(myFlipbookComponent != nullptr && aValue < 0)
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
		if (myPrimarySpeedIndex != -1) bullet->mySpeed = myPlayerStatUpgrades[myPrimarySpeedIndex].myCurrentValue;
		if (myPrimaryDamageIndex != -1) bullet->myDamage = myPlayerStatUpgrades[myPrimaryDamageIndex].myCurrentValue;
		if (myPrimaryRangeIndex != -1) bullet->myRange = myPlayerStatUpgrades[myPrimaryRangeIndex].myCurrentValue;
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

	UE_LOG(LogTemp, Error, TEXT("No Upgrade found for %s when adding bonus"), *aName);
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

void ALV_Player::LoadUpgrades()
{
	if (myUpgradeData != nullptr)
	{
		for (int i = 0; i < myUpgradeData->myPlayerStatUpgrades.Num(); i++)
		{
			myPlayerStatUpgrades.Add(myUpgradeData->myPlayerStatUpgrades[i]);
		}
	}

	myPrimaryFireRateIndex = LoadSingleUpgrade(myPrimaryFireRate);
	if (myPrimaryFireRateIndex == -1) return;

	myPrimaryDamageIndex = LoadSingleUpgrade(myPrimaryDamage);
	if (myPrimaryDamageIndex == -1) return;

	myPrimaryRangeIndex = LoadSingleUpgrade(myPrimaryRange);
	if (myPrimaryRangeIndex == -1) return;

	myPrimarySpeedIndex = LoadSingleUpgrade(myPrimarySpeed);
	if (myPrimarySpeedIndex == -1) return;

	myPrimaryImpactIndex = LoadSingleUpgrade(myPrimaryImpact);
	if (myPrimaryImpactIndex == -1) return;

	myPrimaryCastIndex = LoadSingleUpgrade(myPrimaryCast);
	if (myPrimaryCastIndex == -1) return;

	myMovementSpeedIndex = LoadSingleUpgrade(myMovementSpeed);
	if (myMovementSpeedIndex == -1) return;

	myHealthIndex = LoadSingleUpgrade(myHealth);
	if (myHealthIndex == -1) return;
}

int ALV_Player::LoadSingleUpgrade(const FString& aName)
{
	int index = GetPlayerUpgradeIndex(aName);
	if (index == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("No Upgrade found for %s"), *aName);
	}
	else
	{
		myPlayerStatUpgrades[index].myCurrentValue = myPlayerStatUpgrades[index].myBaseValue;
		UE_LOG(LogTemp, Warning, TEXT("Upgrade found for %s is %f"), *aName, myPlayerStatUpgrades[index].myCurrentValue);
	}
	return index;
}