// Fill out your copyright notice in the Description page of Project Settings.


#include "UPNPGameInstance.h"
#include "GetPortListCallbackProxy.h"
#include "SimpleUPNPBlueprintLibrary.h"

DEFINE_LOG_CATEGORY(UPNPGameInstanceLog);

void UUPNPGameInstance::Init()
{
	Super::Init();

	PortListCallbackProxy = UGetPortListCallbackProxy::CreateProxyObjectForGetPortList(this, true, true, false, TEXT(""));
	PortListCallbackProxy->OnSuccess.AddDynamic(this, &UUPNPGameInstance::OnGetPortListSucceed);
	PortListCallbackProxy->OnFailure.AddDynamic(this, &UUPNPGameInstance::OnGetPortListFail);
	PortListCallbackProxy->Activate();
}

void UUPNPGameInstance::OnGetPortListSucceed(const TArray<FSimpleUPNPInfo>& PortList, ESimpleUPNPErrorCode ErrorCode)
{
	UE_LOG(UPNPGameInstanceLog, Log, TEXT("OnGetPortListSucceed : %d"), PortList.Num());

	FUPNPDeviceInfo DeviceInfo;
	if (USimpleUPNPBlueprintLibrary::GetDeviceInfo(DeviceInfo))
	{
		UE_LOG(UPNPGameInstanceLog, Log, TEXT("Manufacturer : %s"), *DeviceInfo.Manufacture.Manufacturer);
	}
	else
	{
		UE_LOG(UPNPGameInstanceLog, Error, TEXT("Failed to get device information."));
	}
}

void UUPNPGameInstance::OnGetPortListFail(const TArray<FSimpleUPNPInfo>& PortList, ESimpleUPNPErrorCode ErrorCode)
{
	UE_LOG(UPNPGameInstanceLog, Error, TEXT("Failed OnGetPortListFail : %d"), ErrorCode);
}