// Fill out your copyright notice in the Description page of Project Settings.
#include "MyPlayerState.h"

#include "AbilitySystemComponent.h"
#include "GAS/Attributes/AttributeSetHealth.h"

AMyPlayerState::AMyPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	auto abilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	abilitySystemComponent->SetIsReplicated(true);

	auto attributeSetHealth = CreateDefaultSubobject<UAttributeSetHealth>(TEXT("AttributeSetHealth"));
	attributeSetHealth->Initialize(100.0f);
	
	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;
}
