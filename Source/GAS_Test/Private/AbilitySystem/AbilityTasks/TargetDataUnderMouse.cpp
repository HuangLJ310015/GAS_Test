// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled) //客户端
	{
		SendMouseCursorData();
	} 
	else // 服务端
	{
		//获取 能力句柄
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		//获取 激活预测键
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		// 绑定 TargetData 接收回调
		AbilitySystemComponent.Get()
			->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey)
			.AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		//若TargetData已经被设置，则主动调用下回调（为了避免 在绑定前 数据 就已经到了）
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			//告知服务器 正在等待 TargetData (只会增加该任务权重)
			SetWaitingOnRemotePlayerData();			
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//作用域预测窗口， 仅当前作用域有效
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	//向服务端发送 数据（Data）
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	//确保 能力当前还处于 活跃状态
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		//广播代理
		ValidData.Broadcast(DataHandle);
	}
	
}

//接收复制数据的回调
void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	//消耗数据 （获取数据的同时，告知 能力系统组件 不需要再缓存该数据了）
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	//确保 能力当前还处于 活跃状态
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		//广播代理
		ValidData.Broadcast(DataHandle);
	}
}
