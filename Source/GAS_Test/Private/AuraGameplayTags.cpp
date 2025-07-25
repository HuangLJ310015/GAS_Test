// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"

#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	
	/*
	 *		Primary
	 */
	GameplayTags.Attributes_Primary_Strength = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString(TEXT("力量 (增加 物理伤害)")));
	GameplayTags.Attributes_Primary_Intelligence = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), FString(TEXT("智力 (增加 魔法伤害)")));
	GameplayTags.Attributes_Primary_Resilience = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"), FString(TEXT("韧性 (增加 护甲和护甲穿透)")));
	GameplayTags.Attributes_Primary_Vigor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"), FString(TEXT("精力 (增加生命值)")));
	
	/*
 	 *		Secondary
 	 */
	GameplayTags.Attributes_Secondary_Armor = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), FString(TEXT("护甲 (减少受到的伤害，提高格挡几率)")));
	GameplayTags.Attributes_Secondary_ArmorPenetration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), FString(TEXT("护甲穿透 (忽略一定百分比的敌人护甲, 增加暴击概率)")));
	GameplayTags.Attributes_Secondary_BlockChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), FString(TEXT("格挡几率 (有几率将受到的伤害减半)")));
	GameplayTags.Attributes_Secondary_CriticalHitChance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), FString(TEXT("暴击几率 (有几率造成暴击)")));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), FString(TEXT("暴击伤害 (暴击时额外伤害加成)")));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), FString(TEXT("暴击抗性 (降低攻击敌人的暴击几率)")));
	GameplayTags.Attributes_Secondary_HealthRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), FString(TEXT("生命再生 (每秒恢复的生命值)")));
	GameplayTags.Attributes_Secondary_ManaRegeneration = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), FString(TEXT("魔力再生 (每秒恢复的魔力值)")));
	GameplayTags.Attributes_Secondary_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString(TEXT("生命上限 (可获得的最大生命值)")));
	GameplayTags.Attributes_Secondary_MaxMana = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), FString(TEXT("魔力上限 (可获得的最大魔力值)")));
	
	/*
	 *		Vital
	 */
	// GameplayTags.Attributes_Vital_Health = GameplayTagsManager.AddNativeGameplayTag(
	// 	FName("Attributes.Vital.Health"), FString(TEXT("生命值")));
	// GameplayTags.Attributes_Vital_Mana = GameplayTagsManager.AddNativeGameplayTag(
	// 	FName("Attributes.Vital.Mana"), FString(TEXT("魔力值")));

	/*
	 *		Input Tags
	 */
	GameplayTags.InputTag_LMB = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.LMB"), FString(TEXT("鼠标左键 的 InputTag")));
	GameplayTags.InputTag_RMB = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.RMB"), FString(TEXT("鼠标右键 的 InputTag")));
	GameplayTags.InputTag_1 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.1"), FString(TEXT("按键‘1’ 的 InputTag")));
	GameplayTags.InputTag_2 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.2"), FString(TEXT("按键‘2’ 的 InputTag")));
	GameplayTags.InputTag_3 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.3"), FString(TEXT("按键‘3’ 的 InputTag")));
	GameplayTags.InputTag_4 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.4"), FString(TEXT("按键‘4’ 的 InputTag")));
}
