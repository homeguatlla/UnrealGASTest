// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GAS/AbilityInputDefinition.h"
#include "GAS/Attributes/AttributeSetHealth.h"

AMyPlayerState::AMyPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	mAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	mAbilitySystemComponent->SetIsReplicated(true);
	mAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	auto attributeSetHealth = CreateDefaultSubobject<UAttributeSetHealth>(TEXT("AttributeSetHealth"));
	attributeSetHealth->Initialize(100.0f);
	
	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerState::AMyPlayerState %s"), *GetName());

	RegisterAttributesDelegates();
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerState::BeginPlay %s"), *GetName());
}

void AMyPlayerState::RegisterAttributesDelegates()
{
	// Attribute change callbacks
	auto healthAttributeSet = mAbilitySystemComponent->GetSet<UAttributeSetHealth>();
	mHealthChangedDelegateHandle = mAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		healthAttributeSet->GetHealthAttribute()).AddUObject(this, &AMyPlayerState::OnHealthChanged);
}

void AMyPlayerState::RegisterAbilities()
{
	if(HasAuthority() || mAbilitySystemComponent)
	{
		return;
	}

	//TODO ability should inherid from an interface where to get the InputID instead of hardcoded here as Heal
	for (TSubclassOf<UGameplayAbility>& ability : mCharacterAbilities)
	{
		mAbilitySystemComponent->GiveAbility(
            FGameplayAbilitySpec(
            	ability,
            	1,
            	static_cast<int32>(EAbilityInputID::Heal),
            	this
            )
        );
	}
}

void AMyPlayerState::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerState::OnHealthChanged %s health attribute modified"), *GetName());
}
