// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratingTile/GeneratingTileManager.h"

// Sets default values
AGeneratingTileManager::AGeneratingTileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// default values
	TileSize = 100.f;
	Speed = 200.f;
}

// Called when the game starts or when spawned
void AGeneratingTileManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeTiles();
}

// Called every frame
void AGeneratingTileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAndRecycleTiles(DeltaTime);
}

void AGeneratingTileManager::InitializeTiles()
{
	if (!TileClass) return;

	// Spawn the first tile to determine its size
	FVector Location(0, 0, 0);
	FActorSpawnParameters SpawnParams;
	AGeneratingTileController* FirstTile = GetWorld()->SpawnActor<AGeneratingTileController>(TileClass, Location, FRotator::ZeroRotator, SpawnParams);

	if (FirstTile)
	{
		// Get the size of the first tile and initialize TileSize
		TileSize = FirstTile->GetTileSize();
		Tiles.Add(FirstTile);

		// Spawn the remaining tiles using the determined TileSize
		for (int32 i = 1; i < 9; ++i)
		{
			Location.X = i * TileSize;
			AGeneratingTileController* NewTile = GetWorld()->SpawnActor<AGeneratingTileController>(TileClass, Location, FRotator::ZeroRotator, SpawnParams);

			if (NewTile)
			{
				Tiles.Add(NewTile);
			}
		}
	}
}


void AGeneratingTileManager::MoveAndRecycleTiles(float DeltaTime)
{
	for (AGeneratingTileController* Tile : Tiles) {
		FVector Location = Tile->GetActorLocation();

		// Reverse the direction by subtracting instead of adding
		Location.X -= Speed * DeltaTime;

		// Check if the tile has moved past the leftmost boundary
		if (Location.X < 0)
		{
			// Move the tile to the front of the line
			Location.X += TileSize * 9;
			Tile->SetActorLocation(Location);

			// Optionally, spawn a random actor after the tile has been moved
			// SpawnRandomActorOnTile(Tile);
		}
		else
		{
			Tile->SetActorLocation(Location);
		}
	}
}

void AGeneratingTileManager::SpawnRandomActorOnTile(AGeneratingTileController* Tile)
{
	if (SpawnableActors.Num() == 0) return;

	int32 RandomIndex = FMath::RandRange(0, SpawnableActors.Num() - 1);
	TSubclassOf<AActor> ActorToSpawn = SpawnableActors[RandomIndex];

	if (ActorToSpawn)
	{
		// Get the bounds of the tile
		FVector TileBounds = Tile->GetTileBounds();

		// Calculate the spawn location
		FVector TileLocation = Tile->GetActorLocation();
		FVector SpawnLocation = TileLocation;
		SpawnLocation.Z += TileBounds.Z + 20.f; // Add the tile's half-height and an additional vertical offset

		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}