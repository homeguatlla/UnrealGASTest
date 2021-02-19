#include "AttributeSetHealth.h"
#include "Engine/DemoNetDriver.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"

void UAttributeSetHealth::Initialize(float maxHealth)
{
	MaxHealth = maxHealth;
	InitHealth(MaxHealth);
}

void UAttributeSetHealth::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetHealth, Health, COND_None, REPNOTIFY_Always);
}

void UAttributeSetHealth::OnRep_Health(const FGameplayAttributeData& oldHealth) const
{
	//Attribute will be modified.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetHealth, Health, oldHealth);

	//we can add here anything we want to happen once the attribute is modified.
}

void UAttributeSetHealth::PreAttributeChange(const FGameplayAttribute& attribute, float& newValue)
{
	Super::PreAttributeChange(attribute, newValue);

	//Use this method basically to clamp!
	//Just before attribute modifies we have the chance to verify it
	if (attribute == GetHealthAttribute())
	{
		ensureMsgf(newValue < MaxHealth && newValue >= 0.0f, TEXT("Health is outside range [0, %f]"), MaxHealth);
		newValue = FMath::Clamp<float>(newValue, 0.0f, MaxHealth);
	}
}

void UAttributeSetHealth::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//Called when one effect modifies the BaseValue attribute
	//The BaseValue is already modified but not replicated yet
	//So, we can clamp it here before replication
	
}
