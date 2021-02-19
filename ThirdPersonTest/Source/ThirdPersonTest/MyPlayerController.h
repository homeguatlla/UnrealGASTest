// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONTEST_API AMyPlayerController : public APlayerController
{
public:
	AMyPlayerController();
	void AcknowledgePossession(APawn* P) override;
	
protected:
	void OnPossess(APawn* aPawn) override;
	void OnUnPossess() override;
	void BeginPlay() override;
	
private:
	GENERATED_BODY()
	
};
