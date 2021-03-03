#pragma once

class AMyPlayerState;
class UAbilitySystemComponent;

class AbilitySystemComponentBuilder
{
public:
	AbilitySystemComponentBuilder();
	~AbilitySystemComponentBuilder() = default;
	
	AbilitySystemComponentBuilder& WithAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent);
	AbilitySystemComponentBuilder& WithInputComponent(UInputComponent* PlayerInputComponent);
	AbilitySystemComponentBuilder& WithPlayerState(AMyPlayerState* PlayerState);
	AbilitySystemComponentBuilder& WithCharacter(ACharacter* Character);
	
	void Build();

private:
	UAbilitySystemComponent* mAbilitySystemComponent;
	UInputComponent* mPlayerInputComponent;
	AMyPlayerState* mPlayerState;
	ACharacter* mCharacter;
	bool mIsInitialized;
};
