// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LV_Data.h"
#include "LV_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbookComponent;
class UPaperFlipbook;
class UArrowComponent;
class ALV_Bullet;
class ULV_DataAsset;

UCLASS()
class LINEARVANIA_API ALV_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALV_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Right(float aValue);

	void PlayerJump();

	void PlayerStopJump();

	void Shoot();

	void StopShoot();

	void SpawnBullet();

	void AddBonus(const FString& aName, float aValue);

private:
	int GetPlayerUpgradeIndex(const FString& aName);

	void LoadUpgrades();

	int LoadSingleUpgrade(const FString& aName);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbook* myJumpFlipbook = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbook* myRunFlipbook = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbook* myIdleFlipbook = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbook* myShootFlipbook = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbook* myJumpShootFlipbook = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	USpringArmComponent* mySpringArm = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UCameraComponent* myCameraComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperFlipbookComponent* myFlipbookComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	TSubclassOf<ALV_Bullet> myBulletBP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UArrowComponent* myShootPlace = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	TArray<FPlayerStatUpgrade> myPlayerStatUpgrades;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	ULV_DataAsset* myUpgradeData = nullptr;

private:
	bool myIsShooting = false;

	bool myCanShoot = false;

	float myCurrentShootTime = 0;

	int myCurrentHealth = 0;

////////////////
//UPGRADES
////////////////
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimaryFireRate = "PrimaryFireRate";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimaryDamage = "PrimaryDamage";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimaryRange = "PrimaryRange";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimarySpeed = "PrimarySpeed";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimaryImpact = "PrimaryImpact";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myPrimaryCast = "PrimaryCast";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myMovementSpeed = "MovementSpeed";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	FString myHealth = "Health";

private:
	int myPrimaryFireRateIndex = 0;

	int myPrimaryDamageIndex = 0;

	int myPrimaryRangeIndex = 0;

	int myPrimarySpeedIndex = 0;

	int myPrimaryImpactIndex = 0;

	int myPrimaryCastIndex = 0;

	int myMovementSpeedIndex = 0;

	int myHealthIndex = 0;
};
