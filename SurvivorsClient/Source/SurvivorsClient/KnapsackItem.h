// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldItem/ItemData.h"
#include "KnapsackItem.generated.h"


USTRUCT(BlueprintType)
struct FItemAttribute
{
	GENERATED_USTRUCT_BODY()
public:
	void initItemAttribute(TMap<EItemAttribute, UObject*> _itemAttributes) {
		itemAttributes = _itemAttributes;
	}
	//Item 属性
	TMap<EItemAttribute, UObject*> itemAttributes;
};

/**
 * 
 */
UCLASS()
class SURVIVORSCLIENT_API UKnapsackItem : public UObject
{
	GENERATED_BODY()
public:
	//构造函数
	UKnapsackItem();

	
	//初始化Item
	void initUKnapsackItem(int _itemId, int singleDurability, int64 singleSpawnTimeStamps, TMap<EItemAttribute, UObject*> _itemAttributes);

	//初始化Item
	void initUKnapsackItem(int _itemId, TArray<int> durability, TArray<int64> spawnTimeStamps, TArray<FItemAttribute> _itemAttributesList);
	
public:
	//获取当前KnapsackItem的数量
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	int getCount();

	//判断是否为空
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	static bool isEmptyItem(UKnapsackItem* currentItem);


public:
	//ItemID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	int itemId;

	//Item 属性
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemAttribute> itemAttributesList;
	
	//当前耐久度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	TArray<int> currentDurability;

	//Item 创建的时间戳
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	TArray<int64> spawnTimeStamp;

public:
	static const int emptyId = -1000;

	
};
