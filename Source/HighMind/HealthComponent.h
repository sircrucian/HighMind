// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIGHMIND_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
    
public:	
	// Sets default values for this component's properties
	UHealthComponent();

    float GetHealth() const { return Health;}

    UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <=0.0f;}

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;
    
    UFUNCTION()
    void OnTakeAnyDamage( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = ( ClampMin = 0.0f, ClampMax = 1000.0f ), Category= "Health")
    float MaxHealth = 100.0f;
    
private:
    float Health = 0.0f;
    

		
};
