// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"


//初始化
void UFoodItem::initFoodItem(int _itemId, int _maturity)
{
	//ItemID
	itemId = _itemId;
	//熟度
	maturityMax = 5;
	maturity = _maturity;
	//饮食次数
	eatCountMax = 10;
	remainEatCount = eatCountMax;
	
}

//设置熟度
float UFoodItem::setMaturity(int _maturity)
{
	maturity = _maturity;
	return maturity;
}

//饮食一次
float UFoodItem::eatOnce()
{
	remainEatCount -= 1;
	return remainEatCount;
}


