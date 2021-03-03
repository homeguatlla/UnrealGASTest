#include "AbilitySystemComponentBuilder.h"


#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/Character.h"
#include "ThirdPersonTest/MyPlayerState.h"
#include "ThirdPersonTest/GAS/AbilityInputDefinition.h"

AbilitySystemComponentBuilder::AbilitySystemComponentBuilder() :
mAbilitySystemComponent{nullptr},
mPlayerInputComponent{nullptr},
mPlayerState{nullptr},
mCharacter{nullptr},
mIsInitialized{false}
{
}

AbilitySystemComponentBuilder& AbilitySystemComponentBuilder::WithAbilitySystemComponent(
	UAbilitySystemComponent* AbilitySystemComponent)
{
	mAbilitySystemComponent = AbilitySystemComponent;
	
	return *this;
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
	if(!mIsInitialized && mAbilitySystemComponent && mPlayerInputComponent && mPlayerState && mCharacter)
	{
		mAbilitySystemComponent->BindAbilityActivationToInputComponent(
        mPlayerInputComponent,
        FGameplayAbilityInputBinds(
            FString("ConfirmTarget"),
            FString("CancelTarget"),
            FString("EAbilityInputID"),
            static_cast<int32>(EAbilityInputID::Confirm),
            static_cast<int32>(EAbilityInputID::Cancel)
		));
		mAbilitySystemComponent->InitAbilityActorInfo(mPlayerState, mCharacter);
		mPlayerState->RegisterAbilities();
		
		mIsInitialized = true;
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponentBuilder::Build Built!"));
	}
}
