#pragma once

#include "CoreMinimal.h"

#include "AbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 *
 */
UCLASS()
class WIZARDBRAWL_API UGameplayAbilityBase : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
    UMaterialInstance* UIMaterial;

    UFUNCTION(BlueprintCallable, Category = "AbilityBase")
    FGameplayAbilityInfo GetAbilityInfo();

};
