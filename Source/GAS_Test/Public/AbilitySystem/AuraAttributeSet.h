// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class GAS_TEST_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//仅适合Clamp
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	
	/* Begin ~ Primary Attribute */
	UPROPERTY(ReplicatedUsing=OnRep_Strength,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);

	UPROPERTY(ReplicatedUsing=OnRep_Intelligence,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);

	UPROPERTY(ReplicatedUsing=OnRep_Resilience,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);

	UPROPERTY(ReplicatedUsing=OnRep_Vigor,BlueprintReadOnly,Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);
	/* End ~ Primary Attribute */


	/* Begin ~ Secondary Attribute */
	UPROPERTY(ReplicatedUsing=OnRep_Armor,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData Armor; //护甲
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UPROPERTY(ReplicatedUsing=OnRep_ArmorPenetration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration; //护甲穿透
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UPROPERTY(ReplicatedUsing=OnRep_BlockChance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData BlockChance; //格挡几率
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitChance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance; //暴击几率
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitDamage,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage; //暴击伤害
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UPROPERTY(ReplicatedUsing=OnRep_CriticalHitResistance,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance; //暴击抗性
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	UPROPERTY(ReplicatedUsing=OnRep_HealthRegeneration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration; //生命再生
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	UPROPERTY(ReplicatedUsing=OnRep_ManaRegeneration,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration; //魔力再生
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth; //最大生命值
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana,BlueprintReadOnly,Category="Secondary Attributes")
	FGameplayAttributeData MaxMana; //最大魔力值
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	/* End ~ Secondary Attribute */


	/* Begin ~ Vital Attribute */
	UPROPERTY(ReplicatedUsing=OnRep_Health,BlueprintReadOnly,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);
	
	UPROPERTY(ReplicatedUsing=OnRep_Mana,BlueprintReadOnly,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	/* End ~ Vital Attribute */
	


	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};

