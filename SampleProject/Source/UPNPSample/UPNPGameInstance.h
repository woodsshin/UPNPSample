// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UPNPGameInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(UPNPGameInstanceLog, Log, All);

class UGetPortListCallbackProxy;

/**
 * 
 */
UCLASS()
class UPNPSAMPLE_API UUPNPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	UPROPERTY()
	UGetPortListCallbackProxy* PortListCallbackProxy;

	UFUNCTION()
	void OnGetPortListSucceed(const TArray<FSimpleUPNPInfo>& PortList, ESimpleUPNPErrorCode ErrorCode);

	UFUNCTION()
	void OnGetPortListFail(const TArray<FSimpleUPNPInfo>& PortList, ESimpleUPNPErrorCode ErrorCode);
};
