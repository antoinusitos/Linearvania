// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LV_Player.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbookComponent;
class UPaperFlipbook;
class UArrowComponent;
class ALV_Bullet;

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

	void AddShootRateBonus(float aValue);

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
	float myShootRate = 0.2f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LV")
	float myCurrentShootRate = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	float myMinShootRate = 0.05f;

	float myBonusShootRate = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UArrowComponent* myShootPlace = nullptr;

private:
	bool myIsShooting = false;

	bool myCanShoot = false;

	float myCurrentShootTime = 0;
};
