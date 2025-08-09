// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	checkf(AuraContext,TEXT("AuraContext 未设置"));

	//添加输入映射
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(AuraContext,0);
	}

	//是否显示光标
	bShowMouseCursor = true;
	//默认光标类型
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	//不锁定光标到视口
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	//捕获光标后 不影藏光标
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//转换为增强输入组件
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	//绑定Action
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerController::Move);

	//绑定 能力Action
	AuraInputComponent->BindAbilityActions(InputConfig, this, &AAuraPlayerController::AbilityInputTagPressed,
		&AAuraPlayerController::AbilityInputTagReleased, &AAuraPlayerController::AbilityInputTagHeld);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
	AutoRun();

}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	
	if (APawn* ControlPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//拿到InputAction的值 
	const FVector2D InputActionVector = InputActionValue.Get<FVector2D>();
	
	//获取控制器Yaw的旋转
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	//将旋转转换为单位方向向量
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlPawn = GetPawn())
	{
		ControlPawn->AddMovementInput(ForwardDirection,InputActionVector.Y);
		ControlPawn->AddMovementInput(RightDirection,InputActionVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility),false,CursorHit);
	// GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());


	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		// 鼠标下是否有目标
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	}
	else
	{
		const APawn* ControlPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlPawn->GetActorLocation(), CachedDestination))
			{
				//清理过去的样条点
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					// DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() -1];
				bAutoRunning = true;
			}
		}

		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}
