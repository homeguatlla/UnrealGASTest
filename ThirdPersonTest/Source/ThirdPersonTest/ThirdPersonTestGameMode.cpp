// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonTestGameMode.h"
#include "ThirdPersonTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

void AThirdPersonTestGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Begin play starts to BeginPlay all actors.
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestGameMode::BeginPlay"));
}

void AThirdPersonTestGameMode::StartPlay()
{
	Super::StartPlay();
	//The game starts once. It starts as soon the server-client has PostLogin and BeginPlay executed.
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestGameMode::StartPlay"));
}

void AThirdPersonTestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	//New player is properly created, the player controller and character exists and are linked properly.
	//The postlogin is executed on clients after its BeginPlay.
	//The postlogin is executed on server before the GameMode::BeginPlay
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestGameMode::PostLogin %s"), *NewPlayer->GetName());
}

AThirdPersonTestGameMode::AThirdPersonTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default playerController class to our Blueprinted playerController
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/MyPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
