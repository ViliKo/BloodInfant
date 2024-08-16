// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratingTileController.h"
#include "GeneratingTileManager.generated.h"


UCLASS()
class UNREALKILLER_API AGeneratingTileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratingTileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "GeneratingTileManager")
	TSubclassOf<AGeneratingTileController> TileClass;

	UPROPERTY(EditAnywhere, Category = "GeneratingTileManager")
	TArray<TSubclassOf<AActor>> SpawnableActors;


	UPROPERTY(EditAnywhere, Category = "GeneratingTileManager")
	float TileSize;

	UPROPERTY(EditAnywhere, Category = "GeneratingTileManager")
	float Speed;

	TArray<AGeneratingTileController*> Tiles;

	void InitializeTiles();

	void MoveAndRecycleTiles(float DeltaTime);

	void SpawnRandomActorOnTile(AGeneratingTileController* Tile);
};
