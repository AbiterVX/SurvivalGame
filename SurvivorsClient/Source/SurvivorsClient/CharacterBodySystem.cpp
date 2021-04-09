// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBodySystem.h"
#include "WorldItem/FoodItem.h"
#include "WorldItem/FoodItemData.h"
#include "Engine/Engine.h"


UCharacterBodySystem::UCharacterBodySystem()
{
	//----------角色的身体属性
	//最大身体属性
	bodyAttributeMax.Add(ECharacterBodyAttribute::hp, 100.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::hungry, 1200.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::thirsty, 1200.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::bodyReserve, 2400.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::strength, 60.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::vitaminA, 100.0f);
	bodyAttributeMax.Add(ECharacterBodyAttribute::vitaminC, 100.0f);

	//当前身体属性
	currentBodyAttribute.Add(ECharacterBodyAttribute::hp, 100.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::hungry, 0.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::thirsty, 0.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::bodyReserve, 1200.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::strength, 60.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::vitaminA, 100.0f);
	currentBodyAttribute.Add(ECharacterBodyAttribute::vitaminC, 100.0f);

	//身体属性下降速率
	bodyAttributeDecreaseSpeed.Add(ECharacterBodyAttribute::thirsty, 2.0f);
	bodyAttributeDecreaseSpeed.Add(ECharacterBodyAttribute::bodyReserve, 5.0f);
	bodyAttributeDecreaseSpeed.Add(ECharacterBodyAttribute::strength, 1.0f);
	bodyAttributeDecreaseSpeed.Add(ECharacterBodyAttribute::vitaminA, 10.0f);
	bodyAttributeDecreaseSpeed.Add(ECharacterBodyAttribute::vitaminC, 10.0f);

	//身体属性恢复速率
	bodyAttributeRecoverySpeed.Add(ECharacterBodyAttribute::hp, 1.0f);
	bodyAttributeRecoverySpeed.Add(ECharacterBodyAttribute::strength, 0.9f);


	//----------消化系统
	//消化速度
	digestionSpeed.Add(EFoodItemAttribute::carbohyhydrate, 1.5);
	digestionSpeed.Add(EFoodItemAttribute::protein, 1);
	digestionSpeed.Add(EFoodItemAttribute::fat, 0.5);
	digestionSpeed.Add(EFoodItemAttribute::water, 10);
	digestionSpeed.Add(EFoodItemAttribute::cellulose, 3);
	digestionSpeed.Add(EFoodItemAttribute::vitaminA, 1);
	digestionSpeed.Add(EFoodItemAttribute::vitaminC, 1);
	//利用率
	utilizationRate.Add(EFoodItemAttribute::carbohyhydrate, 0.9);
	utilizationRate.Add(EFoodItemAttribute::protein, 0.7);
	utilizationRate.Add(EFoodItemAttribute::fat, 0.7);
	utilizationRate.Add(EFoodItemAttribute::water, 1);
	utilizationRate.Add(EFoodItemAttribute::cellulose, 0);
	utilizationRate.Add(EFoodItemAttribute::vitaminA, 1);
	utilizationRate.Add(EFoodItemAttribute::vitaminC, 1);
	//单位能量
	unitEnergy.Add(EFoodItemAttribute::carbohyhydrate, 10);
	unitEnergy.Add(EFoodItemAttribute::protein, 20);
	unitEnergy.Add(EFoodItemAttribute::fat, 40);
	unitEnergy.Add(EFoodItemAttribute::water, 0);
	unitEnergy.Add(EFoodItemAttribute::cellulose, 0);
	unitEnergy.Add(EFoodItemAttribute::vitaminA, 0);
	unitEnergy.Add(EFoodItemAttribute::vitaminC, 0);
	//当前所占的空间
	currentCapacity.Add(EFoodItemAttribute::carbohyhydrate, 0);
	currentCapacity.Add(EFoodItemAttribute::protein, 0);
	currentCapacity.Add(EFoodItemAttribute::fat, 0);
	currentCapacity.Add(EFoodItemAttribute::water, 0);
	currentCapacity.Add(EFoodItemAttribute::cellulose, 0);
	currentCapacity.Add(EFoodItemAttribute::vitaminA, 0);
	currentCapacity.Add(EFoodItemAttribute::vitaminC, 0);
}

TArray<ECharacterBodyState> UCharacterBodySystem::Tick(float DeltaTime, EMotionType motionType)
{
	TArray<ECharacterBodyState> state;
	state.Add(ECharacterBodyState::healthy);

	//消化
	digest(DeltaTime);

	//能量消耗
	decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute::bodyReserve, DeltaTime);

	//饥饿
	float hungryAttribute = setcurrentBodyAttribute(ECharacterBodyAttribute::hungry, getTotalCapacity());
	if (FMath::IsNearlyEqual(hungryAttribute, 0, 0.1f)) {
		state.Add(ECharacterBodyState::hungry);
	}
	//口渴
	
	float thirsty = getcurrentBodyAttribute(ECharacterBodyAttribute::thirsty);
	if (thirsty > 0 && !FMath::IsNearlyEqual(thirsty, 0, 0.1f)) {
		thirsty = decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute::thirsty, DeltaTime);
		if (FMath::IsNearlyEqual(thirsty, 0, 0.1f)) {
			state.Add(ECharacterBodyState::thirsty);
		}
	}
	else {
		decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute::bodyReserve, DeltaTime);
	}
	
	//运动
	float strength = getcurrentBodyAttribute(ECharacterBodyAttribute::strength);
	float strengthMax = getBodyAttributeMax(ECharacterBodyAttribute::strength);
	if (motionType == EMotionType::run) {
		strength = decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute::strength, DeltaTime);
		if (FMath::IsNearlyEqual(strength, 0, 0.1f)) {
			state.Add(ECharacterBodyState::tired);
		}
	}
	else {
		if (!FMath::IsNearlyEqual(strength, strengthMax, 0.1f)) {
			increaseCharacterBodyAttributeValue(ECharacterBodyAttribute::strength, DeltaTime);
		}
	}
	
	return state;
}

//减少身体属性的值
float UCharacterBodySystem::decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute attribute, float deltaTime, float decreaseValue)
{
	float* currentValue = currentBodyAttribute.Find(attribute);
	if (decreaseValue == -1) {
		decreaseValue = (*bodyAttributeDecreaseSpeed.Find(attribute));
	}
	decreaseValue *= deltaTime;

	if ((*currentValue) > 0) {
		(*currentValue) -= decreaseValue;
		if ((*currentValue) < 0) {
			(*currentValue) = 0;
		}
		return (*currentValue);
	}
	else {
		return 0;
	}
}

//增加身体属性的值
float UCharacterBodySystem::increaseCharacterBodyAttributeValue(ECharacterBodyAttribute attribute, float deltaTime, float additionValue)
{
	float* currentValue = currentBodyAttribute.Find(attribute);
	float* maxValue = bodyAttributeMax.Find(attribute);
	if (additionValue == -1) {
		additionValue = (*bodyAttributeRecoverySpeed.Find(attribute));
	}
	additionValue *= deltaTime;

	if ((*currentValue) < (*maxValue)) {
		(*currentValue) += additionValue;
		if ((*currentValue) > (*maxValue)) {
			(*currentValue) = (*maxValue);
		}
		return (*currentValue);
	}
	else {
		return (*maxValue);
	}
}

//获取当前身体属性的值
float UCharacterBodySystem::getcurrentBodyAttribute(ECharacterBodyAttribute attribute)
{
	return (*currentBodyAttribute.Find(attribute));
}

//获取当前身体属性最大值
float UCharacterBodySystem::getBodyAttributeMax(ECharacterBodyAttribute attribute)
{
	return (*bodyAttributeMax.Find(attribute));
}

//获取当前身体属性百分比
float UCharacterBodySystem::getBodyAttributePercent(ECharacterBodyAttribute attribute)
{
	return (*currentBodyAttribute.Find(attribute)) / (*bodyAttributeMax.Find(attribute));
}

//设置当前身体属性
float UCharacterBodySystem::setcurrentBodyAttribute(ECharacterBodyAttribute attribute, float value)
{
	(*currentBodyAttribute.Find(attribute)) = value;
	return (*currentBodyAttribute.Find(attribute));
}

//减少消化系统中的某类物质
float UCharacterBodySystem::decreaseCurrentCapacity(EFoodItemAttribute attribute, float decreaseValue)
{
	float* capacity = currentCapacity.Find(attribute);
	(*capacity) -= decreaseValue;
	if ((*capacity) < 0) {
		(*capacity) = 0;
	}
	return (*capacity);
}

//添加消化系统中的某类物质
float UCharacterBodySystem::increaseCurrentCapacity(EFoodItemAttribute attribute, float additionValue)
{
	float* capacity = currentCapacity.Find(attribute);
	(*capacity) += additionValue;
	return (*capacity);
}

//获取当前消化系统总共所占空间
float UCharacterBodySystem::getTotalCapacity()
{
	float totalCapacity = 0;
	for (TPair<EFoodItemAttribute, float>& element: currentCapacity) {
		totalCapacity += element.Value;
	}
	return totalCapacity;
}

//消化
void UCharacterBodySystem::digest(float deltaTime)
{
	float energy = 0;
	for (TPair<EFoodItemAttribute, float>& element : currentCapacity) {
		float _digestionSpeed = (*digestionSpeed.Find(element.Key));
		float _utilizationRate = (*utilizationRate.Find(element.Key));
		float _unitEnergy = (*unitEnergy.Find(element.Key));
		float digestCount = deltaTime * _digestionSpeed;

		ECharacterBodyAttribute attribute;
		if (element.Key == EFoodItemAttribute::water) {
			attribute = ECharacterBodyAttribute::thirsty;
		}
		else if (element.Key == EFoodItemAttribute::vitaminA) {
			attribute = ECharacterBodyAttribute::vitaminA;
		}
		else if (element.Key == EFoodItemAttribute::vitaminC) {
			attribute = ECharacterBodyAttribute::vitaminC;
		}
		else {
			attribute = ECharacterBodyAttribute::bodyReserve;
		}

		if (attribute == ECharacterBodyAttribute::bodyReserve) {
			if (element.Value > digestCount) {
				increaseCharacterBodyAttributeValue(attribute, digestCount, _unitEnergy * _utilizationRate);
				element.Value -= digestCount;
			}
			else {
				increaseCharacterBodyAttributeValue(attribute, element.Value, _unitEnergy * _utilizationRate);
				element.Value = 0;
			}
		}
		else {
			if (element.Value > digestCount) {
				increaseCharacterBodyAttributeValue(attribute, digestCount, _utilizationRate);
				element.Value -= digestCount;
			}
			else {
				increaseCharacterBodyAttributeValue(attribute, element.Value, _utilizationRate);
				element.Value = 0;
			}
		}	
	}
}

//饮食
void UCharacterBodySystem::eatFood(UFoodItem* foodItem)
{
	UFoodItemData* foodItemData = Cast<UFoodItemData>(UItemData::getData(EItemAttribute::Food, foodItem->itemId));
	
	float totalCapacity = getTotalCapacity();
	float maxCapacity = getBodyAttributeMax(ECharacterBodyAttribute::hungry);


	float foodItemCapacityEatOnce = foodItemData->getCapacity() / foodItem->eatCountMax;
	if (totalCapacity + foodItemCapacityEatOnce <= maxCapacity) {
		for (TPair<EFoodItemAttribute, float>& element : currentCapacity) {
			element.Value += foodItemData->getAttribute(element.Key);
		}
	}
	else {
		float rate = (maxCapacity - totalCapacity) / foodItemCapacityEatOnce;
		for (TPair<EFoodItemAttribute, float>& element : currentCapacity) {
			element.Value += foodItemData->getAttribute(element.Key)* rate;
		}
	}
	foodItem->eatOnce();
}


