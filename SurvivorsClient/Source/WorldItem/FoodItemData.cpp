// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItemData.h"


void UFoodItemData::initFoodItemData(int _itemId)
{
	Super::initItemData(_itemId);
	
	carbohydrate = 30;
	protein = 10;
	fat = 15;
	water = 100;
	cellulose = 5;
	vitaminA = 5;
	vitaminC = 5;
	cookRate = 6;
	disease = 11111;
	diseaseProbability = 0.1f;
	
}

float UFoodItemData::getCapacity()
{
	float capacity = 0;
	capacity += carbohydrate;
	capacity += protein;
	capacity += fat;
	capacity += water;
	capacity += cellulose;
	capacity += vitaminA;
	capacity += vitaminC;


	return capacity;
}

float UFoodItemData::getAttribute(EFoodItemAttribute attribute)
{

	switch (attribute)
	{
	case EFoodItemAttribute::carbohyhydrate:
		return carbohydrate;
		break;
	case EFoodItemAttribute::protein:
		return protein;
		break;
	case EFoodItemAttribute::fat:
		return fat;
		break;
	case EFoodItemAttribute::water:
		return water;
		break;
	case EFoodItemAttribute::cellulose:
		return cellulose;
		break;
	case EFoodItemAttribute::vitaminA:
		return vitaminA;
		break;
	case EFoodItemAttribute::vitaminC:
		return vitaminC;
		break;
	default:
		break;
	}

	return 0;
}
