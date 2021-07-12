// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LV_Bullet.generated.h"

class USceneComponent;
class UPaperSpriteComponent;
class UBoxComponent;

UCLASS()
class LINEARVANIA_API ALV_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALV_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	USceneComponent* mySceneComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperSpriteComponent* mySpriteComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LV")
	UBoxComponent* myCollisionComponent;

	FVector myDirection = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	float mySpeed = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	float myDamage = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	float myRange = 0;

private :
	float myBaseGravity = 0;

	FVector myStartPos;

	bool myGravityApplied = false;

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
