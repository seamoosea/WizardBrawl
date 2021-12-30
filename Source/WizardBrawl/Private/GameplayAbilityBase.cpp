#include "GameplayAbilityBase.h"



FGameplayAbilityInfo UGameplayAbilityBase::GetAbilityInfo()
{
    UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
    UGameplayEffect* CostEffect = GetCostGameplayEffect();
    if (CoolDownEffect&& CostEffect)
    {
        float CoolDownDuration = 0;
        CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDownDuration);
        float Cost = 0;
        EAbilityCostType CostType;

        if(CostEffect->Modifiers.Num()>0)
        {
            FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
            EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1,Cost);
            FGameplayAttribute CostAttribute = EffectInfo.Attribute;
            FString AttributeName = CostAttribute.AttributeName;
            if(AttributeName == "Health")
            {
                CostType = EAbilityCostType::Health;
            }
            return FGameplayAbilityInfo(CoolDownDuration, GetClass());

        }

    }

    return FGameplayAbilityInfo();
}
