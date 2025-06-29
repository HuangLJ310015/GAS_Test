// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
	
}

void UAttributeMenuWidgetController::BroadcastInitialValue()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	ensureMsgf(AttributeInfo,TEXT("UAttributeMenuWidgetController.AttributeInfo 未配置"));

	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
