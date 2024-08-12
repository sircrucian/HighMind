// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    Input->BindAction(InputMove, ETriggerEvent::Started, this, &AMainCharacter::MoveForward);
    //Input->BindAction(InputMove, ETriggerEvent::Started, this, &AMainCharacter::SomeCallbackFunc);
}

void AMainCharacter::LookUp(const FInputActionInstance& Instance)
{
    
}

void AMainCharacter::LookAround(float Amount)
{
}

void AMainCharacter::SomeCallbackFunc(const FInputActionInstance& Instance)
{
    FVector VectorValue = Instance.GetValue().Get<FVector>();
    FVector2D AxisValueVector2D = Instance.GetValue().Get<FVector2D>();
    float FloatValue = Instance.GetValue().Get<float>(); 
    bool BoolValue = Instance.GetValue().Get<bool>();
}

void AMainCharacter::MoveForward(const FInputActionInstance& Instance)
{
    FVector VectorValue = Instance.GetValue().Get<FVector>();
    FVector2D AxisValueVector2D = Instance.GetValue().Get<FVector2D>();
    float FloatValue = Instance.GetValue().Get<float>(); 
    bool BoolValue = Instance.GetValue().Get<bool>();
    AddControllerPitchInput(100);
    //GetParentActor()->SetActorTransform()
}

