// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Utils.h"

AMyPlayerController::AMyPlayerController()
{
	if(HasAuthority())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::AMyPlayerController %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AMyPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::AcknowledgePossession Player controller %s, ack pawn: %s"), *GetName(), *P->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::OnPossess player controller %s possess by %s:"), *GetName(), *aPawn->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AMyPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::OnUnPossess %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::BeginPlay %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AMyPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::ProcessPlayerInput %s"), *GetName());
}
