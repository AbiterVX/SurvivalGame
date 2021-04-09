// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EUseItemAction :uint8
{
	none,
	eat,
	attack,
	fire,
	make,
	defense,
	aim,
	reload,
	leave,
};



UCLASS()
class WORLDITEM_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	//构造函数
	AItem();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;


//----------初始化
public:
	//初始化
	UFUNCTION(BlueprintCallable, Category = "Init")
	void initItem(int _itemId, int _currentDurability = 100);

	//从背包项里初始化 Item
	
	UFUNCTION(BlueprintCallable, Category = "Init")
	void initItemFromKnapsack(int _itemId, TMap<EItemAttribute, UObject*> _itemAttributes, int _currentDurability = 100);
	
	//初始化Mesh
	UFUNCTION(BlueprintCallable, Category = "Init")
	void initMesh();

	//是否已初始化过Mesh
	bool hasInitMesh;
	
//----------成员变量
public:
	//Mesh
	UPROPERTY(VisibleAnywhere, Category = "AttributeMesh")
	class UStaticMeshComponent* itemMesh;

public:
	//ItemID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	int itemId = 0;

	
	//属性
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	TMap<EItemAttribute, UObject*> itemAttributes;

	//当前耐久
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attribute")
	int currentDurability;

	//Item 创造的时间戳
	int64 spawnTimeStamp;

//----------配表属性
public:
	//得到ItemName
	static FString getItemName();
	
	//得到IconPath
	FString getIconPath();
	
	//得到单位重量
	static int getUnitWeight();
	
	//得到属性
	static TArray<int> getAttribues();

	//得到创建所需材料
	static TArray<int> getMaterial();

	//获取最大耐久度
	static int getMaxDurability();

	//获取属性
	UObject* getItemAttribute(EItemAttribute attribute);

//----------交互
public:
	//根据Index 获取动作
	EUseItemAction getUseItemAction(int index);

//----------Item 静态函数
public:
	//根据Label查找Item
	static AItem* findItemByLabel(UWorld* currentWorld,FString itemLabel);

	
};
