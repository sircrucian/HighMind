// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

DEFINE_LOG_CATEGORY_STATIC(HealthCharacterLog, All, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIGHMIND_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
    
public:	
	// Sets default values for this component's properties
	UHealthComponent();

    float GetHealth() const { return Health;}

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return FMath::IsNearlyZero(Health);}

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( ClampMin = 0.0f, ClampMax = 1000.0f ), Category= "Health")
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;
    
private:
    float Health = 0.0f;

    FTimerHandle HealTimerHandle;
    
    UFUNCTION()
    void OnTakeAnyDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

    void HealUpdate();
    void SetHealth(float NewHealth);
};
