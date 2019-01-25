// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardeCharacter.h"


// Sets default values
AGuardeCharacter::AGuardeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGuardeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuardeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector test = GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("VECTOR %.2f, %.2f, %.2f"), test.X, test.Y, test.Z));*/

}

// Called to bind functionality to input
void AGuardeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

