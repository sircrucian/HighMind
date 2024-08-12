// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class HIGHMIND_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Camera" )
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Camera" )
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Input")
    UInputAction* InputMove;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input")
    //UEnhancedInputComponent* EnhancedInputComponent;

    UPROPERTY(EditAnywhere, Category="Input")
    TSoftObjectPtr<UInputMappingContext> InputMapping;
    
    void LookUp(const FInputActionInstance& Instance);
    void LookAround(float Amount);

    void SomeCallbackFunc(const FInputActionInstance& Instance);

    void MoveForward(const FInputActionInstance& Amount);
};
