// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PhilipsHueBridge.h"
#include "PhilipsHueDiscovery.generated.h"


UENUM()
enum class EPhilipsHueDiscoveryState : uint8
{
	/** No discovery in progress. */
	Idle,

	/** Discovery using meethue.com in progress. */
	MeetHue,

	/** Discovery using UPNP in progress. */
	Upnp,
};


/**
 * A Philips Hue bridge discovery.
 */
UCLASS(BlueprintType, hidecategories=(Object))
class UPhilipsHueDiscovery
	: public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/** Discover Philips Hue bridges on the network. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	void DiscoverBridges();

	/** Forget all bridges on the network. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	void ForgetBridges();

	/** Gets the current discovery state. */
	UFUNCTION(BlueprintCallable, Category="PhilipsHue|Discovery")
	EPhilipsHueDiscoveryState GetState()
	{
		return State;
	}

protected:

	/**
	 * Process a HTTP response.
	 *
	 * @param HttpResponse The response to process.
	 */
	void ProcessHttpResponse(FHttpResponsePtr HttpResponse, bool Succeeded);

private:

	/** Handles the completion of HTTP requests. */
	void HandleHttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

private:

	/** Collection of discovered bridges. */
	UPROPERTY()
	TArray<UPhilipsHueBridge*> KnownBridges;

	/** Current discovery state. */
	UPROPERTY()
	EPhilipsHueDiscoveryState State;
};
