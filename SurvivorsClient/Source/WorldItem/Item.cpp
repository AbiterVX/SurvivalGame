// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FoodItem.h"



//构造函数
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	hasInitMesh = false;
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	initItem(itemId,100);
	initMesh();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//----------初始化
//初始化
void AItem::initItem(int _itemId, int _currentDurability)
{
	itemId = _itemId;
	currentDurability = _currentDurability;
	if (itemId == 3 || itemId == 4 || itemId == 5 || itemId == 6) {
		//添加Food属性
		UFoodItem* foodItem = NewObject<UFoodItem>();
		foodItem->initFoodItem(itemId);
		itemAttributes.Add(EItemAttribute::Food, foodItem);
	}
}


//从背包项里初始化 Item
void AItem::initItemFromKnapsack(int _itemId, TMap<EItemAttribute, UObject*> _itemAttributes, int _currentDurability)
{
	itemId = _itemId;
	itemAttributes = _itemAttributes;
	currentDurability = _currentDurability;
}

//初始化Mesh
void AItem::initMesh()
{
	if (!hasInitMesh) {	
		if (itemId != 0) {
			FStringAssetReference asset = "/Game/Asset/Resources/Item/Item" + FString::FromInt(itemId) + ".Item" + FString::FromInt(itemId);
			UObject* itemObj = asset.ResolveObject();
			UStaticMesh* itemStaticMesh = Cast<UStaticMesh>(itemObj);

			if (itemStaticMesh != nullptr){
				hasInitMesh = true;
				itemMesh->SetStaticMesh(itemStaticMesh);
			}
		}
		//spawnTimeStamp;
	}
}

//----------配表属性
//得到ItemName
FString AItem::getItemName()
{
	return "";
}

//得到IconPath
FString AItem::getIconPath()
{
	return "";
}

//得到单位重量
int AItem::getUnitWeight()
{
	return 10;
}

//得到属性
TArray<int> AItem::getAttribues()
{
	TArray<int> temp;
	return temp;
}

//得到创建所需材料
TArray<int> AItem::getMaterial()
{
	TArray<int> temp;
	return temp;
}

//获取最大耐久度
int AItem::getMaxDurability()
{
	return 0;
}

//获取属性
UObject* AItem::getItemAttribute(EItemAttribute attribute)
{
	return (*itemAttributes.Find(attribute));
}


//----------交互
//根据Index 获取动作
EUseItemAction AItem::getUseItemAction(int index)
{
	EUseItemAction result = EUseItemAction::none;
	if (index == 1) {
		if (itemId == 3 || itemId == 4 || itemId == 5 || itemId == 6) {
			result = EUseItemAction::eat;
		}
	}
	
	return result;
}


//----------Item 静态函数
//根据Label查找Item
AItem* AItem::findItemByLabel(UWorld* currentWorld,FString itemLabel)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(currentWorld, AActor::StaticClass(), Actors);

	for (AActor* currentActor : Actors){
		if (itemLabel == currentActor->GetActorLabel()) {
			return Cast<AItem>(currentActor);
			break;
		}
	}
	return nullptr;
}
