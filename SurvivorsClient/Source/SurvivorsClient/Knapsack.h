// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KnapsackItem.h"
#include "Knapsack.generated.h"

/**
	背包
 * 
 */
UCLASS()
class SURVIVORSCLIENT_API UKnapsack : public UObject
{
	GENERATED_BODY()


public:
	//初始化背包
	void initUKnapsack(int length);

//----------背包Item项相关操作
public:
	//添加背包Item项到对应Index
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	UKnapsackItem* addKnapsackItemByIndex(int index, UKnapsackItem*& currentItem);
	
	//添加背包Item项
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	int addKnapsackItem(UKnapsackItem*& currentItem);
	
	//移除对应Index的背包Item项
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	void removeKnapsackItem(int index);
	
	//根据Index修改背包Item项
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	UKnapsackItem* modifyKnapsackItem(int index, UKnapsackItem*& currentItem);
	
	//根据Index得到背包Item项
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	UKnapsackItem* getKnapsackItem(int index);
	
	//交换两个Item位置
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	void exchangeKnapsackItem(UKnapsack* knapsackA,int indexA, UKnapsack* knapsackB, int indexB);

public:
	//创建一个背包Item项
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	static UKnapsackItem* createKnapsackItem(int _itemId, TArray<int> durability, TArray<int64> spawnTimeStamps, TArray<FItemAttribute> _itemAttributesList);

public:
	//背包内的Item列表
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	TArray<UKnapsackItem*> itemList;
	
	//空Item，便于判别
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	UKnapsackItem* emptyItem;
};
