// Fill out your copyright notice in the Description page of Project Settings.


#include "KnapsackItem.h"


//构造函数
UKnapsackItem::UKnapsackItem()
{
	
	TArray<int> durability;
	TArray<int64> spawnTimeStamps;
	TArray<FItemAttribute> _itemAttributesList;
	durability.Add(emptyId);
	spawnTimeStamps.Add(emptyId);
	initUKnapsackItem(emptyId,durability, spawnTimeStamps, _itemAttributesList);
	
}


//初始化Item
void UKnapsackItem::initUKnapsackItem(int _itemId, int singleDurability, int64 singleSpawnTimeStamps, TMap<EItemAttribute, UObject*> _itemAttributes)
{
	TArray<int> durability;
	TArray<int64> spawnTimeStamps;
	TArray<FItemAttribute> _itemAttributesList;
	durability.Add(singleDurability);
	spawnTimeStamps.Add(singleSpawnTimeStamps);

	FItemAttribute newItemAttribute;
	newItemAttribute.initItemAttribute(_itemAttributes);
	_itemAttributesList.Add(newItemAttribute);
	initUKnapsackItem(_itemId, durability, spawnTimeStamps, _itemAttributesList);
}

//初始化Item
void UKnapsackItem::initUKnapsackItem(int _itemId, TArray<int> durability, TArray<int64> spawnTimeStamps, TArray<FItemAttribute> _itemAttributesList)
{
	this->itemId = _itemId;
	currentDurability = durability;
	spawnTimeStamp = spawnTimeStamps; 
	itemAttributesList = _itemAttributesList;
}


//获取当前KnapsackItem的数量
int UKnapsackItem::getCount()
{
	return currentDurability.Num();
}

//判断是否为空
bool UKnapsackItem::isEmptyItem(UKnapsackItem* currentItem)
{
	if (currentItem->itemId == emptyId) {
		return true;
	}
	return false;
}

