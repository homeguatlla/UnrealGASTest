// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ThirdPersonTestGameMode.generated.h"

UCLASS(minimalapi)
class AThirdPersonTestGameMode : public AGameModeBase
{
protected:
	virtual void BeginPlay() override;
public:
	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
private:
	GENERATED_BODY()

public:
	AThirdPersonTestGameMode();
};



