#pragma once

class AMyPlayerState;
class UAbilitySystemComponent;

class AbilitySystemComponentBuilder
{
public:
	AbilitySystemComponentBuilder();
	~AbilitySystemComponentBuilder() = default;
	
	AbilitySystemComponentBuilder& WithInputComponent(UInputComponent* PlayerInputComponent);
	AbilitySystemComponentBuilder& WithPlayerState(AMyPlayerState* PlayerState);
	AbilitySystemComponentBuilder& WithCharacter(ACharacter* Character);
	
	void Build();

private:
	UInputComponent* mPlayerInputComponent;
	AMyPlayerState* mPlayerState;
	ACharacter* mCharacter;
	bool mIsInitialized;
};
