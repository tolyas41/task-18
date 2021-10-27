// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/CapsuleComponent.h"
#include "HammerCollider.h"

AHammerCollider::AHammerCollider()
{
	HammerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hammer Collider"));
	SetRootComponent(HammerCapsule);
}

