// Fill out your copyright notice in the Description page of Project Settings.


#include "Knapsack.h"


//----------
//初始化背包
void UKnapsack::initUKnapsack(int length)
{
	emptyItem = NewObject<UKnapsackItem>();
	for (int i = 0; i < length;i++) {
		itemList.Add(emptyItem);
	}
}



//----------背包Item项相关操作
//添加背包Item项到对应Index
UKnapsackItem* UKnapsack::addKnapsackItemByIndex(int index, UKnapsackItem*& currentItem)
{
	if (itemList[index] == emptyItem) {
		itemList[index] = currentItem;
		return itemList[index];
	}
	else {
		return nullptr;
	}
}

//添加背包Item项
int UKnapsack::addKnapsackItem(UKnapsackItem*& currentItem)
{
	int resultIndex = -1;
	for (int i = 0; i < itemList.Num();i++) {
		if (UKnapsackItem::isEmptyItem(itemList[i])) {
			itemList[i] = currentItem;
			resultIndex = i;
			break;
		}
	}
	return resultIndex;
}

//移除对应Index的背包Item项
void UKnapsack::removeKnapsackItem(int index)
{
	if (itemList[index] != emptyItem && index != -1) {
		itemList[index] = emptyItem;
	}
}

//根据Index修改背包Item项
UKnapsackItem* UKnapsack::modifyKnapsackItem(int index, UKnapsackItem*& currentItem)
{
	itemList[index] = currentItem;
	return itemList[index];
}

//根据Index得到背包Item项
UKnapsackItem* UKnapsack::getKnapsackItem(int index)
{
	return itemList[index];
}

//交换两个Item位置
void UKnapsack::exchangeKnapsackItem(UKnapsack* knapsackA, int indexA, UKnapsack* knapsackB, int indexB)
{
	if (&knapsackA == &knapsackB && indexA== indexB) {
		return;
	}
	UKnapsackItem* tempItem = knapsackA->itemList[indexA];
	knapsackA->itemList[indexA] = knapsackB->itemList[indexB];
	knapsackB->itemList[indexB] = tempItem;
}

//----------
//创建一个背包Item项
UKnapsackItem* UKnapsack::createKnapsackItem(int _itemId, TArray<int> durability, TArray<int64> spawnTimeStamps, TArray<FItemAttribute> _itemAttributesList)
{
	UKnapsackItem* currentKnapsackITem = NewObject<UKnapsackItem>();
	currentKnapsackITem->initUKnapsackItem(_itemId, durability, spawnTimeStamps, _itemAttributesList);
	return currentKnapsackITem;
}

