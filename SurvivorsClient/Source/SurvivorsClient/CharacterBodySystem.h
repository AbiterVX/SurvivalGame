// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldItem/FoodItemData.h"
#include "CharacterBodySystem.generated.h"


UENUM(BlueprintType)
enum class ECharacterBodyState :uint8
{
	healthy,
	hungry,
	thirsty,
	tired,
	injured,
	dying,
	die,
};

UENUM(BlueprintType)
enum class EMotionType :uint8
{
	idle,
	walk,
	run,
	jump
};


UENUM(BlueprintType)
enum class ECharacterBodyAttribute :uint8
{
	hp,
	hungry,
	thirsty,
	bodyReserve,
	strength,
	vitaminA,
	vitaminC,
};


UCLASS()
class SURVIVORSCLIENT_API UCharacterBodySystem : public UObject
{
	GENERATED_BODY()
public:
	UCharacterBodySystem();

public:
	TArray<ECharacterBodyState> Tick(float DeltaTime, EMotionType motionType);

//----------角色的身体属性
public:
	//最大身体属性
	UPROPERTY(VisibleAnywhere, Category = "BodyAttribute")
	TMap<ECharacterBodyAttribute, float> bodyAttributeMax;

	//当前身体属性
	UPROPERTY(VisibleAnywhere, Category = "BodyAttribute")
	TMap<ECharacterBodyAttribute, float> currentBodyAttribute;
	
	//身体属性下降速率
	UPROPERTY(VisibleAnywhere, Category = "BodyAttribute")
	TMap<ECharacterBodyAttribute, float> bodyAttributeDecreaseSpeed;

	//身体属性恢复速率
	UPROPERTY(VisibleAnywhere, Category = "BodyAttribute")
	TMap<ECharacterBodyAttribute, float> bodyAttributeRecoverySpeed;


public:
	//减少身体属性的值
	float decreaseCharacterBodyAttributeValue(ECharacterBodyAttribute attribute, float deltaTime, float decreaseValue = -1);

	//增加身体属性的值
	float increaseCharacterBodyAttributeValue(ECharacterBodyAttribute attribute, float deltaTime, float additionValue = -1);

	//获取当前身体属性的值
	UFUNCTION(BlueprintCallable, Category = "BodyAttribute")
	float getcurrentBodyAttribute(ECharacterBodyAttribute attribute);

	//获取当前身体属性最大值
	UFUNCTION(BlueprintCallable, Category = "BodyAttribute")
	float getBodyAttributeMax(ECharacterBodyAttribute attribute);

	//获取当前身体属性百分比
	UFUNCTION(BlueprintCallable, Category = "BodyAttribute")
	float getBodyAttributePercent(ECharacterBodyAttribute attribute);

	//设置当前身体属性
	float setcurrentBodyAttribute(ECharacterBodyAttribute attribute, float value);

//----------消化系统
public:
	//消化速度
	UPROPERTY(VisibleAnywhere, Category ="DigestiveSystem")
	TMap<EFoodItemAttribute, float> digestionSpeed;

	//利用率
	UPROPERTY(VisibleAnywhere, Category = "DigestiveSystem")
	TMap<EFoodItemAttribute, float> utilizationRate;

	//单位能量
	UPROPERTY(VisibleAnywhere, Category = "DigestiveSystem")
	TMap<EFoodItemAttribute, float> unitEnergy;

	//当前所占的空间
	UPROPERTY(VisibleAnywhere, Category = "DigestiveSystem")
	TMap<EFoodItemAttribute, float> currentCapacity;

	//减少消化系统中的某类物质
	float decreaseCurrentCapacity(EFoodItemAttribute attribute, float decreaseValue);

	//添加消化系统中的某类物质
	float increaseCurrentCapacity(EFoodItemAttribute attribute, float additionValue);

	

	//获取当前消化系统总共所占空间
	float getTotalCapacity();

	//消化
	void digest(float deltaTime);

	//饮食
	void eatFood(class UFoodItem* foodItem );

	
	//储存能量
	//float gainWeight();
};
