// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_TEST_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UAuraAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
