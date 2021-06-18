// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LV_PowerUp.generated.h"

class USceneComponent;
class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class LINEARVANIA_API ALV_PowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALV_PowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	USceneComponent* mySceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LV")
	UBoxComponent* myCollisionComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UPaperSpriteComponent* mySpriteComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	FString myBonusName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LV")
	float myBonusPercent = 0;

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
