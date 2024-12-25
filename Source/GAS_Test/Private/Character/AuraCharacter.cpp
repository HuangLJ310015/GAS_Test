// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//Character 跟随 移动方向 旋转 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f,400.f,0.f);
	//限制角色在平面上
	GetCharacterMovement()->bConstrainToPlane = true;

	//Pawn 不 跟随控制器旋转
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	
	
}
