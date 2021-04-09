// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class WORLDITEM_API UFoodItem : public UObject
{
	GENERATED_BODY()
public:
	
	//初始化
	void initFoodItem(int _itemId, int _maturity = 0);
	
	//设置熟度
	UFUNCTION(BlueprintCallable)
	float setMaturity(int _maturity);

	//饮食一次
	UFUNCTION(BlueprintCallable)
	float eatOnce();

	//获取食物数据
	//class UFoodItemData* getFoodItemData();
public:
	//ItemID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int itemId;

	//最大熟度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int maturityMax;
	//熟度
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int maturity;
	
	//最大饮食次数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int eatCountMax;
	//饮食次数
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int remainEatCount;
	
	


private:
	class FoodItemData* itemData;

};
