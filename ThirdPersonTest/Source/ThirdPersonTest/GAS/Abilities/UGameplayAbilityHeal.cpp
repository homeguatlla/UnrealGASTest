#include "UGameplayAbilityHeal.h"

bool UGameplayAbilityHeal::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Warning, TEXT("UGameplayAbilityHeal::CanActivateAbility"));
	return true;
}

void UGameplayAbilityHeal::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	UE_LOG(LogTemp, Warning, TEXT("UGameplayAbilityHeal::CancelAbility"));
}

void UGameplayAbilityHeal::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("UGameplayAbilityHeal::ActivateAbility"));
}
