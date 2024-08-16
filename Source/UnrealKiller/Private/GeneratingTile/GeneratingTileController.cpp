// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratingTile/GeneratingTileController.h"

// Sets default values
AGeneratingTileController::AGeneratingTileController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeneratingTileController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneratingTileController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorLocalRotation(FRotator(0, DeltaTime * 20, 0));

}

FVector AGeneratingTileController::GetTileBounds() const
{
    if (TileMesh)
    {
        FBoxSphereBounds Bounds = TileMesh->Bounds;
        return Bounds.BoxExtent; // Half dimensions of the tile
    }
    return FVector::ZeroVector;
}

float AGeneratingTileController::GetTileSize() const
{
    // Assuming the tile size is represented by its bounds
    FVector TileBounds = GetComponentsBoundingBox().GetSize();
    return TileBounds.X;  // Assuming the size you want is along the X-axis
}