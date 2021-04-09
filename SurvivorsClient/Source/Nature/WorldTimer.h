// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldTimer.generated.h"



UENUM(BlueprintType)
enum class ETimeSectionType :uint8
{
	minutes,
	hour,
	day,
	year,
};

UENUM(BlueprintType)
enum class ETimeStateType :uint8
{
	SunRise,
	Sun,
	SunSet,
	Moon,
};


UCLASS()
class NATURE_API AWorldTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldTimer();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;



//----------
public:
	//游戏内每天的时间
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	int secondsPerDay;
	//季节
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	TArray<int> season;

	//Handle Timer 句柄
	FTimerHandle MemberTimerHandle;

	
	int64 startGameTime;
	UWorld* world;

	int hourUnit;
	int minutesUnit;
public:
	//暂停 Timer
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void pauseTimer();

	//取消暂停 Timer
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void unpauseTimer();

	//获取当前时间
	UFUNCTION(BlueprintCallable, Category = "Timer")
	TMap<ETimeSectionType,int> getGameTime();

	//格式化打印当前时间
	UFUNCTION(BlueprintCallable, Category = "Timer")
	FString getGameTimeInFString();

	//获取当天的占比
	UFUNCTION(BlueprintCallable, Category = "Timer")
	float getCurrentDayPercent();

	UFUNCTION(BlueprintCallable, Category = "Timer")
	ETimeStateType getCurrentTimeState();

};
