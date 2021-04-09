// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OverlapItemData.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSCLIENT_API UOverlapItemData : public UObject
{
	GENERATED_BODY()
	
public:
	class AItem* item;
	float distance;

	bool operator()(const UOverlapItemData* A, const UOverlapItemData* B) const;
};
