#pragma once
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetHealth.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class UAttributeSetHealth : public UAttributeSet
{	
	GENERATED_BODY()
public:
	UAttributeSetHealth() = default;
	~UAttributeSetHealth() = default;

	void Initialize(float maxHealth);
private:
	UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& oldHealth) const;
	
	void PreAttributeChange(const FGameplayAttribute& attribute, float& newValue) override;
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetHealth, Health)
	
	float MaxHealth;
};
