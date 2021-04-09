// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "FoodItemData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EFoodItemAttribute :uint8
{
	carbohyhydrate,
	protein,
	fat,
	water,
	cellulose,
	vitaminA,
	vitaminC,
};

UCLASS()
class WORLDITEM_API UFoodItemData : public UItemData
{
	GENERATED_BODY()
	
public:

	void initFoodItemData(int _itemId);

	float getCapacity();

	float getAttribute(EFoodItemAttribute attribute);
public:
	//属性
	float carbohydrate;
	float protein;
	float fat;
	float water;
	float cellulose;
	float vitaminA;
	float vitaminC;
	int eatCountMax;
	//烹饪速率
	int cookRate;

	//疾病
	int disease;
	//疾病概率
	float diseaseProbability;


};
