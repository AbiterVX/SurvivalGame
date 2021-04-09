// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/Engine.h"
#include "WorldItem/Item.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "OverlapItemData.h"
#include "CharacterBodySystem.h"
#include "WorldItem/FoodItem.h"
#include "GameFramework/CharacterMovementComponent.h"


//构造函数
ASurvivalCharacter::ASurvivalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//移动
	
	isRun = false;
	isMoveBackward = false;
	isCrouch = false;
	walkSpeedMax = 300.0f;
	runSpeedMax = 600.0f;


	//背包
	inventoryShortcutSize = 10;
	inventoryMainSize = 15;
	
	currentItemInRightHands = nullptr;
	currentItemShortcutIndex = -1;
	//射线检测
	rayCastLength = 800.0f;
	
	inventoryMainState = true;
	
}

//起始帧调用
void ASurvivalCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	//初始化背包
	inventoryShortcut = NewObject<UKnapsack>();
	inventoryMain = NewObject<UKnapsack>();
	
	inventoryShortcut->initUKnapsack(inventoryShortcutSize);
	inventoryMain->initUKnapsack(inventoryMainSize);
	
	//初始化身体属性系统
	bodySystem = NewObject<UCharacterBodySystem>();
	
}

//每帧调用
void ASurvivalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//----------身体属性消耗
	//获取运动类别
	
	EMotionType motionType;
	float velocity = GetVelocity().Size();
	if (velocity > walkSpeedMax && isRun && !isMoveBackward) {
		motionType = EMotionType::run;
	}
	else if(FMath::IsNearlyEqual(velocity, walkSpeedMax, 0.1f)){
		motionType = EMotionType::walk;
	}
	else {
		motionType = EMotionType::idle;
	}
	
	//身体属性消耗
	TArray<ECharacterBodyState> state = bodySystem->Tick(DeltaTime, motionType);
	
}

//绑定输入
void ASurvivalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//----------人物移动
	//移动
	PlayerInputComponent->BindAxis("MoveForward", this, &ASurvivalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASurvivalCharacter::MoveRight);
	//鼠标转动
	PlayerInputComponent->BindAxis("Turn", this, &ASurvivalCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASurvivalCharacter::AddControllerPitchInput);
	//跳跃
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASurvivalCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASurvivalCharacter::StopJump);
	//奔跑
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASurvivalCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASurvivalCharacter::StopRun);
	//蹲下
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASurvivalCharacter::SetCrouch);
	
	//----------背包
	FString str_prefix(TEXT("GetItem"));
	
	for (int i = 1; i <= inventoryShortcutSize;i++) {
		if (i< inventoryShortcutSize) {
			FName currentName(*(str_prefix + FString::FromInt(i)));
			PlayerInputComponent->BindAction<F_useItemShortcut_Delegate>(currentName, IE_Pressed, this, &ASurvivalCharacter::useItemShortcut, i - 1);
		}
		else {
			FName currentName(*(str_prefix + FString::FromInt(i%10)));
			PlayerInputComponent->BindAction<F_useItemShortcut_Delegate>(currentName, IE_Pressed, this, &ASurvivalCharacter::useItemShortcut, i - 1);
		}
		
	}

	//----------物品
	//丢弃当前
	//PlayerInputComponent->BindAction("Discard", IE_Pressed, this, &ASurvivalCharacter::discardCurrentItem);
	

	//使用物品
	for (int i = 1; i <= 4;i++) {
		FName actionName(  *FString::Printf(TEXT("UseItem_%d"), i)   );
		PlayerInputComponent->BindAction<F_useCurrentItem_Delegate>(actionName, IE_Pressed, this, &ASurvivalCharacter::useCurrentItem, i);
	}
	
}




//----------移动
//输入绑定:向前行走
void ASurvivalCharacter::MoveForward(float Rate)
{
	if (GetCharacterMovement()->MovementMode == MOVE_Swimming) {
		if ((Controller != NULL) && (Rate != 0.0f))
		{
			APlayerCameraManager* currentCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
			FVector forwardDirection = currentCamera->GetActorForwardVector();
			
			if (Rate < 0.0f) {
				isMoveBackward = true;
			}
			else {
				isMoveBackward = false;
			}

			if (isRun) {
				if (Rate > 0.0f && bodySystem->getcurrentBodyAttribute(ECharacterBodyAttribute::strength) > 0.1f) {
					AddMovementInput(forwardDirection, Rate);
				}
				else {
					AddMovementInput(forwardDirection, Rate * walkSpeedMax / runSpeedMax);
				}
			}
			else {
				AddMovementInput(forwardDirection, Rate * walkSpeedMax / runSpeedMax);
			}

			
			SetActorRotation(forwardDirection.Rotation());
		}
		
	}
	else {
		if ((Controller != NULL) && (Rate != 0.0f))
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			if (Rate < 0.0f) {
				isMoveBackward = true;
			}
			else {
				isMoveBackward = false;
			}

			if (isRun) {
				if (Rate > 0.0f && bodySystem->getcurrentBodyAttribute(ECharacterBodyAttribute::strength) > 0.1f) {
					AddMovementInput(Direction, Rate);
				}
				else {
					AddMovementInput(Direction, Rate * walkSpeedMax / runSpeedMax);
				}
			}
			else {
				AddMovementInput(Direction, Rate * walkSpeedMax / runSpeedMax);
			}

		}
	}

	
}

//输入绑定:向右行走
void ASurvivalCharacter::MoveRight(float Rate)
{
	if ((Controller != NULL) && (Rate != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		if (isRun) {
			if (!isMoveBackward && bodySystem->getcurrentBodyAttribute(ECharacterBodyAttribute::strength) > 0.1f) {
				AddMovementInput(Direction, Rate);
			}
			else {
				AddMovementInput(Direction, Rate * walkSpeedMax / runSpeedMax);
			}
		}
		else {
			AddMovementInput(Direction, Rate * walkSpeedMax / runSpeedMax);
		}

	}
		



	
}

//输入绑定:开始跳跃
void ASurvivalCharacter::StartJump()
{
	if (GetCharacterMovement()->MovementMode == MOVE_Swimming) {
		FVector direction = FVector::UpVector;

		AddMovementInput(direction, walkSpeedMax);
	}
	else {
		bPressedJump = true;
	}
	
}

//输入绑定:停止跳跃
void ASurvivalCharacter::StopJump()
{
	bPressedJump = false;
}

//输入绑定:开始奔跑
void ASurvivalCharacter::StartRun()
{
	isRun = true;
}

//输入绑定:停止奔跑
void ASurvivalCharacter::StopRun()
{
	isRun = false;
}

//输入绑定:设置是否蹲下
void ASurvivalCharacter::SetCrouch()
{
	isCrouch = !isCrouch;
}

//输入绑定:镜头左右移动
void ASurvivalCharacter::AddControllerYawInput(float Rate)
{
	if (inventoryMainState) {
		APawn::AddControllerYawInput(Rate);
	}
}

//输入绑定:镜头上下移动
void ASurvivalCharacter::AddControllerPitchInput(float Rate)
{
	if (inventoryMainState) {
		APawn::AddControllerPitchInput(Rate);
	}
}



//----------使用物品
//0-9 输入绑定:根据索引使用快捷背包里的物品
void ASurvivalCharacter::useItemShortcut(int index)
{
	
// 	FString itemName = "BP_Item" + FString::FromInt(index);
// 	AItem* currentItem = AItem::findItemByLabel(GetWorld(),itemName);
// 	if (currentItem!= nullptr) {
// 		//AItem* newItem = GetWorld()->SpawnActor<AItem>();
// 		currentItem->itemMesh->SetSimulatePhysics(false);
// 		currentItem->SetActorEnableCollision(false);
// 		USkeletalMeshComponent* mesh = GetMesh();
// 		currentItem->AttachToComponent(Cast<USceneComponent>(mesh), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHandSocket");
// 		currentItemInRightHands = currentItem;
// 		currentItemShortcutIndex = index;
// 	}
// 	else {
// 
// 	}
	
	
	if (currentItemShortcutIndex == index) {
		return;
	}

	if (currentItemInRightHands) {
		currentItemInRightHands->Destroy();
	}


	UKnapsackItem* knapsackItem = inventoryShortcut->itemList[index];
	if (!UKnapsackItem::isEmptyItem(knapsackItem)) {
		FStringAssetReference asset = "Blueprint'/Game/Asset/BP/Item/BP_Item.BP_Item'";
		UObject* itemObj = asset.ResolveObject();
		UBlueprint* bluePrintObj = Cast<UBlueprint>(itemObj);
		AItem* newItem = Cast<AItem>( GetWorld()->SpawnActor<AActor>(bluePrintObj->GeneratedClass) );


		newItem->initItemFromKnapsack(knapsackItem->itemId, knapsackItem->itemAttributesList[0].itemAttributes);
		newItem->initMesh();
		newItem->itemMesh->SetSimulatePhysics(false);
		newItem->SetActorEnableCollision(false);

		USkeletalMeshComponent* mesh = GetMesh();
		newItem->AttachToComponent(Cast<USceneComponent>(mesh), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHandSocket");
		currentItemInRightHands = newItem;
		currentItemShortcutIndex = index;

		//广播:使用Item时，发出对应item在快捷背包内的索引
		useItem_Delegate.Broadcast(index);
	}
	else {
		currentItemInRightHands = nullptr;
		currentItemShortcutIndex = -1;

		//广播:使用Item时，发出对应item在快捷背包内的索引
		useItem_Delegate.Broadcast(-1);
	}

	
}

//Q 输入绑定:丢弃当前物品
void ASurvivalCharacter::discardCurrentItem()
{
	
	if (currentItemInRightHands != nullptr) {
		currentItemInRightHands->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		currentItemInRightHands->AttachToActor(Cast<AActor>(GetWorld()), FAttachmentTransformRules::SnapToTargetIncludingScale);
		currentItemInRightHands->SetActorEnableCollision(true);
		currentItemInRightHands->itemMesh->SetSimulatePhysics(true);
		currentItemInRightHands = nullptr;
		inventoryShortcut->removeKnapsackItem(currentItemShortcutIndex);
		currentItemShortcutIndex = -1;
		
		//广播:使用Item时，发出对应item在快捷背包内的索引
		useItem_Delegate.Broadcast(-1);
	}
	
}

//E 输入绑定:与对应物品交互
void ASurvivalCharacter::interactCurrentItem(AItem* currentItem, int interactType)
{
	if (interactType == 1) {
		if (currentItem != nullptr) {
// 			discardCurrentItem();
// 			currentItem->itemMesh->SetSimulatePhysics(false);
// 			currentItem->SetActorEnableCollision(false);
// 			USkeletalMeshComponent* mesh = GetMesh();
// 			currentItem->AttachToComponent(Cast<USceneComponent>(mesh), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHandSocket");
// 			currentItemInRightHands = currentItem;
			
			
			//----------添加到背包里	
			//耐久
			TArray<int> durability;
			durability.Add(0);
			//时间戳
			TArray<int64> spawnTimeStamps;
			spawnTimeStamps.Add(currentItem->spawnTimeStamp);
			//属性
			TArray<FItemAttribute> _itemAttributesList;
			FItemAttribute tempItemAttribute;
			tempItemAttribute.initItemAttribute(currentItem->itemAttributes);
			_itemAttributesList.Add(tempItemAttribute);
			//创建KnapsackItem
			UKnapsackItem* tempItem = inventoryShortcut->createKnapsackItem(currentItem->itemId, durability, spawnTimeStamps, _itemAttributesList);

			//添加到背包里
			int resultIndex = inventoryShortcut->addKnapsackItem(tempItem);	
			if (resultIndex != -1) {
				currentItem->Destroy();
			}
			
		}
	}
}

//输入绑定:使用当前物品(鼠标左键,鼠标右键,按键R,按键F)
void ASurvivalCharacter::useCurrentItem(int index)
{
	
	if (currentItemInRightHands != nullptr) {
		EUseItemAction actionName = currentItemInRightHands->getUseItemAction(index);
		if (actionName == EUseItemAction::eat) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("UseItem: Eat!"));
			
			UFoodItem* foodItem = Cast<UFoodItem>(currentItemInRightHands->getItemAttribute(EItemAttribute::Food));
			bodySystem->eatFood(foodItem);
			if (foodItem->remainEatCount == 0) {
				currentItemInRightHands->Destroy();
				currentItemInRightHands = nullptr;
				inventoryShortcut->removeKnapsackItem(currentItemShortcutIndex);
				currentItemShortcutIndex = -1;

				//广播:使用Item时，发出对应item在快捷背包内的索引
				useItem_Delegate.Broadcast(-1);
				FString inventoryName = "Shortcut";
				refreshInventory_Delegate.Broadcast(inventoryName);
			}			
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("UseItem: NULL"));
		}
	}
	
}

//输入绑定:显示地图(按键V)
void ASurvivalCharacter::showMap()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NULL"));
}



//----------背包
//获取背包
UKnapsack* ASurvivalCharacter::getKnapsack(FString name)
{
	if (name == "Shortcut") {
		return inventoryShortcut;
	}
	else if (name == "Main") {
		return inventoryMain;
	}
	return nullptr;
	
}




//----------碰撞检测
//获取最近的碰撞Overlap的物品
class AItem* ASurvivalCharacter::getNearestOverlapItem()
{
	if (overlapItems.Num() > 0) {
		return overlapItems[0]->item;
	}
	return nullptr;
}

//添加碰撞Overlap的物品
void ASurvivalCharacter::addOverlapItem(AItem* currentItem)
{
	UOverlapItemData* tempData = NewObject<UOverlapItemData>();
	tempData->item = currentItem;
	tempData->distance = (currentItem->GetActorLocation() - GetActorLocation()).Size();
	overlapItems.Add(tempData);
	overlapItems.Sort();
}

//移除碰撞Overlap的物品
void ASurvivalCharacter::removeOverlapItem(AItem* currentItem)
{
	if (overlapItems.Num() > 0) {
		int index = 0;
		for (int i = 0; i < overlapItems.Num();i++) {
			if (overlapItems[i]->item == currentItem) {
				index = i;
				break;
			}
		}
		overlapItems.RemoveAt(index);
		if (overlapItems.Num() > 0) {
			overlapItems.Sort();
		}
	}
}
