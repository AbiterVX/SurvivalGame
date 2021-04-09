// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapItemData.h"


bool UOverlapItemData::operator()(const UOverlapItemData* A, const UOverlapItemData* B) const
{
	return A->distance < B->distance;
}
