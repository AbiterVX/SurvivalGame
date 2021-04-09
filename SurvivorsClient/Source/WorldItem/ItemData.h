// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tools/json.hpp"
#include "ItemData.generated.h"
using json = nlohmann::json;


UENUM(BlueprintType)
enum class EItemAttribute :uint8
{
	RawMaterial,
	Animal,
	Plant,
	Food,
	Tool,
	Weapon,
	Cloth,
	Handcraft,
	Material,
	Vehicle,
	Building,
	Medicine
};



UCLASS()
class WORLDITEM_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:
	void initItemData(int _itemId);
	static UItemData* getData(EItemAttribute attribute, int itemId);

public:
	//属性
	int itemId;
	FString itemName;
	FString iconPath;
	float unitWeight;
	TArray<int> attribues;
	TArray<int> material;
	int maxDurability;
private:
	const FString dataPath = "111";
};
