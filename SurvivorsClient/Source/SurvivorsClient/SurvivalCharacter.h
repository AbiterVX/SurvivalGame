// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Knapsack.h"
#include "Delegates/DelegateCombinations.h"
#include "SurvivalCharacter.generated.h"


UCLASS()
class SURVIVORSCLIENT_API ASurvivalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivalCharacter();
protected:
	//起始帧
	virtual void BeginPlay() override;
public:	
	//每帧
	virtual void Tick(float DeltaTime) override;
	//设置输入按键
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




//----------移动
public:
	//是否要奔跑(是否在按住Left Shift)
	bool isRun;
	//是否在向后移动
	bool isMoveBackward;
	//是否在蹲下
	bool isCrouch;
	//最大行走速度
	float walkSpeedMax;
	//最大奔跑速度
	float runSpeedMax;

	//主背包状态:开启与关闭
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterAttribute")
	bool inventoryMainState;
private:
	//输入绑定:向前行走
	void MoveForward(float Rate);
	//输入绑定:向右行走
	void MoveRight(float Rate);
	//输入绑定:开始跳跃
	void StartJump();
	//输入绑定:停止跳跃
	void StopJump();
	//输入绑定:开始奔跑
	void StartRun();
	//输入绑定:停止奔跑
	void StopRun();
	//输入绑定:设置是否蹲下
	void SetCrouch();
	//输入绑定:镜头左右移动
	void AddControllerYawInput(float Rate);
	//输入绑定:镜头上下移动
	void AddControllerPitchInput(float Rate);

//----------使用物品
public:
	//当前手中的物品
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	class AItem* currentItemInRightHands;
private:
	//0-9 输入绑定:根据索引使用快捷背包里的物品
	DECLARE_DELEGATE_OneParam(F_useItemShortcut_Delegate, int32);
	void useItemShortcut(int index);

	//Q 输入绑定:丢弃当前物品
	UFUNCTION(BlueprintCallable)
	void discardCurrentItem();

	//E 输入绑定:与对应物品交互
	UFUNCTION(BlueprintCallable)
	void interactCurrentItem(class AItem* currentItem,int interactType);

public:
	//输入绑定:按键0-9 事件调度器。目的:UI蓝图可知按下的具体键，并进行显示。
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(F_UseItem_Delegate, int32, index);
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	F_UseItem_Delegate useItem_Delegate;

	//输入绑定:使用当前物品(鼠标左键,鼠标右键,按键R,按键F)
	DECLARE_DELEGATE_OneParam(F_useCurrentItem_Delegate, int32);
	void useCurrentItem(int index);

	//输入绑定:显示地图(按键V)
	void showMap();

//----------身体属性
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class UCharacterBodySystem* bodySystem;

//----------背包
public:
	//背包:快捷背包
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Knapsack")
	UKnapsack* inventoryShortcut;
	//背包:主背包
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Knapsack")
	UKnapsack* inventoryMain;

	//快捷背包容量
	int inventoryShortcutSize;
	//主背包容量
	int inventoryMainSize;

	//当前使用的快捷背包物品的索引
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Knapsack")
	int currentItemShortcutIndex;

public:
	//刷新背包
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(F_RefreshInventory_Delegate, FString, name);
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	F_RefreshInventory_Delegate refreshInventory_Delegate;
public:
	//获取背包
	UFUNCTION(BlueprintCallable, Category = "Knapsack")
	UKnapsack* getKnapsack(FString name);

//----------碰撞检测
public:
	//当前碰撞Overlap的物品 列表
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Raycast")
	TArray<class UOverlapItemData*> overlapItems;

public:
	//获取最近的碰撞Overlap的物品
	UFUNCTION(BlueprintCallable)
	class AItem* getNearestOverlapItem();
	//添加碰撞Overlap的物品
	UFUNCTION(BlueprintCallable)
	void addOverlapItem(class AItem* currentItem);
	//移除碰撞Overlap的物品
	UFUNCTION(BlueprintCallable)
	void removeOverlapItem(class AItem* currentItem);

private:
	float rayCastLength;

};
