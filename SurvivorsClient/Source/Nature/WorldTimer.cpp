// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTimer.h"
#include "Tools/json.hpp"
#include "Engine.h"

using json = nlohmann::json;

// Sets default values
AWorldTimer::AWorldTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	secondsPerDay = 60*1;  //1080
	hourUnit = 24;
	minutesUnit =  60;

	season.Add(10);
	season.Add(20);
	season.Add(30);
	season.Add(40);

	startGameTime = secondsPerDay/4;
	
}

// Called when the game starts or when spawned
void AWorldTimer::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	

	/*
	json j;
	j["xx"] = "asdasd";
	FString testString(std::string(j["xx"]).c_str());
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, testString);
	*/
}

// Called every frame
void AWorldTimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


//暂停 Timer
void AWorldTimer::pauseTimer()
{
	GetWorldTimerManager().PauseTimer(MemberTimerHandle);
}

//取消暂停 Timer
void AWorldTimer::unpauseTimer()
{
	GetWorldTimerManager().UnPauseTimer(MemberTimerHandle);
}

//获取当前时间
TMap<ETimeSectionType, int> AWorldTimer::getGameTime()
{
	TMap<ETimeSectionType, int> currentGameTime;
	float timeSeconds = 0;
	if (world != nullptr) {
		timeSeconds = world->GetTimeSeconds();
	}
	
	int64 totalTimeSceond = startGameTime + timeSeconds;

	
	//时间映射
	int remainDayTime = totalTimeSceond % secondsPerDay;
	int dayPart = totalTimeSceond / secondsPerDay;
	int yearPart = dayPart / season[season.Num() - 1];
	dayPart = dayPart % season[season.Num() - 1];


	int hourPart = float(remainDayTime) / float(secondsPerDay) * hourUnit;
	int minutesPart = float(remainDayTime % hourUnit) / float(hourUnit) * minutesUnit;

	currentGameTime.Add(ETimeSectionType::year, yearPart);
	currentGameTime.Add(ETimeSectionType::day, dayPart);
	currentGameTime.Add(ETimeSectionType::hour, hourPart);
	currentGameTime.Add(ETimeSectionType::minutes, minutesPart);

	return currentGameTime;
}

//格式化打印当前时间
FString AWorldTimer::getGameTimeInFString()
{
	TMap<ETimeSectionType, int> currentGameTime = getGameTime();

	FString resultTime = FString::Printf(TEXT("Year:%d,Day:%d,Time:%d:%d"), 
		(*currentGameTime.Find(ETimeSectionType::year)),
		(*currentGameTime.Find(ETimeSectionType::day)),
		(*currentGameTime.Find(ETimeSectionType::hour)),
		(*currentGameTime.Find(ETimeSectionType::minutes))  );
		
	return resultTime;
}

//获取当天的占比
float AWorldTimer::getCurrentDayPercent()
{
	TMap<ETimeSectionType, int> currentGameTime;
	float timeSeconds = 0;
	if (world != nullptr) {
		timeSeconds = world->GetTimeSeconds();
	}

	float totalTimeSceond = startGameTime + timeSeconds;
	
	//时间映射
	


	float remainDayTime = totalTimeSceond - float(int(totalTimeSceond) /secondsPerDay)* float(secondsPerDay);
	return remainDayTime / float(secondsPerDay);
}

ETimeStateType AWorldTimer::getCurrentTimeState()
{
	float percent = getCurrentDayPercent();

	if (0.125f <= percent && percent<0.375f) {
		return ETimeStateType::SunRise;
	}
	else if (0.375f <= percent && percent < 0.625f) {
		return ETimeStateType::Sun;
	}
	else if (0.625f <= percent && percent < 0.875f) {
		return ETimeStateType::SunSet;
	}
	else {
		return ETimeStateType::Moon;
	}
}

