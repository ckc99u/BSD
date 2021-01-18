// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	BaseCube = CreateDefaultSubobject<UStaticMeshComponent>("DefaultSceneRoot");
	RootComponent = BaseCube;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshCu(TEXT("/StaticMesh'/Engine/BasicShapes/Cube'"));

	if (MeshCu.Succeeded())
		BaseCube->SetStaticMesh(MeshCu.Object);

}





/*
Reset Base postion
*/
void APlayerBase::Initialize(FVector &_location)
{
	this->SetActorLocation(_location);
}

