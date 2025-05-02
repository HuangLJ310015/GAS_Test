// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * 本项目GameplayTags（单例）
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get(){ return GameplayTags; }
	static void InitializeNativeGameplayTags();

	//Primary Attributes
	FGameplayTag Attributes_Primary_Strength;  //力量
	FGameplayTag Attributes_Primary_Intelligence;  //智力
	FGameplayTag Attributes_Primary_Resilience;  // 韧性
	FGameplayTag Attributes_Primary_Vigor;  //精力
	

	//Secondary Attributes
	FGameplayTag Attributes_Secondary_Armor;    //护甲
	FGameplayTag Attributes_Secondary_ArmorPenetration; //护甲穿透
	FGameplayTag Attributes_Secondary_BlockChance;	//格挡几率
	FGameplayTag Attributes_Secondary_CriticalHitChance;	//暴击几率
	FGameplayTag Attributes_Secondary_CriticalHitDamage;	//暴击伤害
	FGameplayTag Attributes_Secondary_CriticalHitResistance;	//暴击抗性
	FGameplayTag Attributes_Secondary_HealthRegeneration;	//生命再生
	FGameplayTag Attributes_Secondary_ManaRegeneration;	//魔力再生
	FGameplayTag Attributes_Secondary_MaxHealth; //生命上限
	FGameplayTag Attributes_Secondary_MaxMana; //魔力上限

	//Vital Attributes
	// FGameplayTag Attributes_Vital_Health; //生命值
	// FGameplayTag Attributes_Vital_Mana;	//魔力值
	
protected:
	
private:
	static FAuraGameplayTags GameplayTags;
};
