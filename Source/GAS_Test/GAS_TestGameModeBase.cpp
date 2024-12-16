// Copyright Epic Games, Inc. All Rights Reserved.


#include "GAS_TestGameModeBase.h"

#include "Player/AuraPlayerController.h"

AGAS_TestGameModeBase::AGAS_TestGameModeBase()
{
	PlayerControllerClass = AAuraPlayerController::StaticClass();
}
