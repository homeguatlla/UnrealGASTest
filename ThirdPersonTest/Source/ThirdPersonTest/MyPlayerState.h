// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"


#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GAS/Attributes/AttributeSetHealth.h"

#include "MyPlayerState.generated.h"

struct FOnAttributeChangeData;

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class THIRDPERSONTEST_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return mAbilitySystemComponent; }
	void RegisterAbilities();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> mCharacterAbilities;

protected:
	void BeginPlay() override;
	
private:
	void RegisterAttributesDelegates();
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	
	UPROPERTY()
	UAbilitySystemComponent* mAbilitySystemComponent;
	
	// Attribute changed delegate handles
	FDelegateHandle mHealthChangedDelegateHandle;
};
