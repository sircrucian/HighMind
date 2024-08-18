// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Input")
    UInputAction* InputLook;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Movement")
    UCharacterMovementComponent* CharacterMovementComponent;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Enhanced Input")
    //UEnhancedInputComponent* EnhancedInputComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Input")
    UInputMappingContext* InputMapping;

    void MoveInput(const FInputActionInstance& Instance);
    void LookInput(const FInputActionInstance& Instance2);

    void MoveForward(FVector2D Direction, float Value);
    void MoveRight(FVector2D Direction, float Value);

    void LookUp(float Value);
    void LookAround(float Value);
};
