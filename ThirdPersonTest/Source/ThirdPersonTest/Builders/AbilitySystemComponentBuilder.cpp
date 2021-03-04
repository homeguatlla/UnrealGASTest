#include "AbilitySystemComponentBuilder.h"


#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/Character.h"
#include "ThirdPersonTest/MyPlayerState.h"
#include "ThirdPersonTest/GAS/AbilityInputDefinition.h"

AbilitySystemComponentBuilder::AbilitySystemComponentBuilder() :
mPlayerInputComponent{nullptr},
mPlayerState{nullptr},
mCharacter{nullptr},
mIsInitialized{false}
{
}

AbilitySystemComponentBuilder& AbilitySystemComponentBuilder::WithInputComponent(UInputComponent* PlayerInputComponent)
{
	mPlayerInputComponent = PlayerInputComponent;
	return *this;
}

AbilitySystemComponentBuilder& AbilitySystemComponentBuilder::WithPlayerState(AMyPlayerState* PlayerState)
{
	mPlayerState = PlayerState;
	return *this;
}

AbilitySystemComponentBuilder& AbilitySystemComponentBuilder::WithCharacter(ACharacter* Character)
{
	mCharacter = Character;
	return *this;
}

void AbilitySystemComponentBuilder::Build()
{
	if(!mIsInitialized && mPlayerInputComponent && mPlayerState && mCharacter)
	{
		mPlayerState->InitializeAbilitySystemComponent(mPlayerInputComponent, mCharacter);
		mIsInitialized = true;
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponentBuilder::Build Built!"));
	}
}
