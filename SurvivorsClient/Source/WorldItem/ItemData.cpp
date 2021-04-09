// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"
#include "FoodItemData.h"

void UItemData::initItemData(int _itemId)
{
	itemId = _itemId;

	itemName = "Item:" + FString::FromInt(itemId);
	iconPath = ">>>";
	unitWeight = 1;
	
	//attribues;
	//material;

	maxDurability = 1;
}

UItemData* UItemData::getData(EItemAttribute attribute, int itemId)
{
	UItemData* itemData = nullptr;

	if (attribute == EItemAttribute::Food) {
		UFoodItemData* foodItemData = NewObject<UFoodItemData>();
		foodItemData->initFoodItemData(itemId);
		itemData = foodItemData;
	}


	/*
	switch (attribute)
	{
	case EItemAttribute::RawMaterial:
		itemData = nullptr;
		break;
	case EItemAttribute::Animal:
		itemData = nullptr;
		break;
	case EItemAttribute::Plant:
		itemData = nullptr;
		break;
	case EItemAttribute::Food:
		itemData =
		//Cast<UFoodItemData>(itemData)
		break;
	case EItemAttribute::Tool:
		itemData = nullptr;
		break;
	case EItemAttribute::Weapon:
		itemData = nullptr;
		break;
	case EItemAttribute::Cloth:
		itemData = nullptr;
		break;
	case EItemAttribute::Handcraft:
		itemData = nullptr;
		break;
	case EItemAttribute::Material:
		itemData = nullptr;
		break;
	case EItemAttribute::Vehicle:
		itemData = nullptr;
		break;
	case EItemAttribute::Building:
		itemData = nullptr;
		break;
	case EItemAttribute::Medicine:
		itemData = nullptr;
		break;
	default:
		break;
	}
	*/


	return itemData;
}
