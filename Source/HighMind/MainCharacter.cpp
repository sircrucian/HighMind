// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    SpringArmComponent->SetupAttachment(RootComponent);
    CameraComponent->SetupAttachment(SpringArmComponent);
    
    
    //UEnhancedInputSubsystemInterface* EnhancedInputSubsystemInterface = APlayerController->
    
    //CharacterMovementComponent = CreateDefaultSubobject<UCharacterMovementComponent>("Move Component");

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

    if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            const FModifyContextOptions& Options = FModifyContextOptions();
            Subsystem->AddMappingContext(InputMapping,0, Options );
        }
    }
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
    
    Input->BindAction(InputMove, ETriggerEvent::Triggered, this, &AMainCharacter::MoveInput);
    Input->BindAction(InputLook, ETriggerEvent::Triggered, this, &AMainCharacter::LookInput);
}

void AMainCharacter::LookUp(float Value)
{
    AddControllerYawInput(Value);
}

void AMainCharacter::LookAround(float Value)
{
    AddControllerPitchInput(Value);
}

void AMainCharacter::MoveInput(const FInputActionInstance& Instance)
{
    TArray<UInputModifier*> Gris = Instance.GetModifiers();
    //FVector VectorValue = Instance.GetValue().Get<FVector>();
    FVector2D AxisValueVector2D = Instance.GetValue().Get<FVector2D>();
    float FloatValue = Instance.GetValue().Get<float>();
    float FloatForward = AxisValueVector2D.X;
    float FloatRight = AxisValueVector2D.Y;
    //bool BoolValue = Instance.GetValue().Get<bool>();

    //UE_LOG(LogTemp, Warning, TEXT(AxisValueVector2D), TEXT(__FUNCTION__), AxisValueVector2D);
   // UE_LOG(LogTemp, Warning, TEXT( "X = %f"), AxisValueVector2D);
    
    //if (AxisValueVector2D.X != 0){MoveRight(AxisValueVector2D, FloatValue);}

    //FString logMessage = FString::Printf(TEXT("Vector 1: (%.2f, %.2f)"), AxisValueVector2D.X, AxisValueVector2D.Y);
    //FString logMessage1 = FString::Printf(TEXT("Float: (%.2f)"), FloatValue);
    //FString logMessage2 = FString::Printf(TEXT("Float: (%.2f)"), FloatValue);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, logMessage);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, logMessage1);
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, logMessage2);
    
    if (AxisValueVector2D.Y != 0){MoveRight(AxisValueVector2D, FloatRight);}
    if (AxisValueVector2D.X != 0) MoveForward(AxisValueVector2D,  FloatForward);
    //MoveRight(AxisValueVector2D, FloatValue);
}

void AMainCharacter::LookInput(const FInputActionInstance& Instance)
{
    TArray<UInputModifier*> Gris = Instance.GetModifiers();
    //FVector VectorValue = Instance.GetValue().Get<FVector>();
    FVector2D AxisValueVector2D = Instance.GetValue().Get<FVector2D>();
    float FloatValue = Instance.GetValue().Get<float>();
    float FloatForward = AxisValueVector2D.X;
    float FloatRight = AxisValueVector2D.Y;

    FString logMessage2 = FString::Printf(TEXT("X: (%.2f), Y: (%.2f)"), FloatForward, FloatRight);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, logMessage2);
    
    //if (AxisValueVector2D.Y != 0){LookUp (FloatForward);}
    //if (AxisValueVector2D.X != 0) LookAround(FloatRight);
    if(FloatForward != 0) LookUp (FloatForward);
    if(FloatRight != 0)LookAround(FloatRight);
}

void AMainCharacter::MoveForward(FVector2D Direction,float Value)
{
    if ((Controller != NULL) && (Value != 0.0f) )
    {// find out which way is forward
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling

        //if (CharacterMovementComponent->IsMovingOnGround() || CharacterMovementComponent->IsFalling()  )
        {
            Rotation.Pitch = 1.0f;
        }

        // add movement in that direction
    
        //const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
    //GetParentActor()->SetActorTransform()
}

void AMainCharacter::MoveRight(FVector2D Direction, float Value)
{
    if ((Controller != NULL) && (Value != 0.0f) )
    {
        FRotator Rotation = Controller->GetControlRotation();
        // Limit pitch when walking or falling

        //if (CharacterMovementComponent->IsMovingOnGround() || CharacterMovementComponent->IsFalling()  )
        {
            Rotation.Pitch = 1.0f;
        }
        
        const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}



