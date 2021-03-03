#pragma once

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	// 0 None
	None				UMETA(DisplayName = "None"),
    // 1 Confirm
    Confirm				UMETA(DisplayName = "Confirm"),
    // 2 Cancel
    Cancel				UMETA(DisplayName = "Cancel"),
    // 3 Sprint
    Sprint				UMETA(DisplayName = "Sprint"),
    // 4 Jump
    Jump				UMETA(DisplayName = "Jump"),
	// 5 Heal
    Heal				UMETA(DisplayName = "Heal")
};