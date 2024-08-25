// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);
    
    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
    }
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    //UE_LOG(HealthCharacterLog, Display, TEXT("Damage: %0.f", Damage));
    if(Damage <=0 || IsDead() || !GetWorld()) return;
    
    SetHealth(Health - Damage);

    if(IsDead())
    {
        OnDeath.Broadcast();
    }
    else if(AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void UHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if(FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}



