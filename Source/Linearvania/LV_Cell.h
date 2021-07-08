// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LV_Cell.generated.h"

class UArrowComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class LINEARVANIA_API ALV_Cell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALV_Cell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	bool myHasTopLink = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	bool myHasBottomLink = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	bool myHasRightLink = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	bool myHasLeftLink = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	int myX = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LV")
	int myY = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "LV")
	USceneComponent* mySceneComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UArrowComponent* myLeftArrowComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
		UArrowComponent* myRightArrowComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
		UArrowComponent* myTopArrowComponent = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
		UArrowComponent* myBottomArrowComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UStaticMeshComponent* myLeftCube = nullptr;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UStaticMeshComponent* myRightCube = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UStaticMeshComponent* myTopCube = nullptr;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LV")
	UStaticMeshComponent* myBottomCube = nullptr;

public:
	void GenerateLinks();

	void ShowArrow();

	void AddLinkRight();

};
