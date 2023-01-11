// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
AEldenPlayerCharacter::AEldenPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));

}

// Called when the game starts or when spawned
void AEldenPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEldenPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//디렉션을 컨트롤러 방향으로 변환
	direction = FTransform(GetControlRotation()).TransformVector(direction); 
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
}

// Called to bind functionality to input
void AEldenPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_Horizontal, ETriggerEvent::Triggered, this, &AEldenPlayerCharacter::Horizontal);

	enhancedInputComponent->BindAction(ia_Horizontal, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::Horizontal);

	enhancedInputComponent->BindAction(ia_Vertical, ETriggerEvent::Triggered, this, &AEldenPlayerCharacter::Vertical);

	enhancedInputComponent->BindAction(ia_Vertical, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::Vertical);

	enhancedInputComponent->BindAction(ia_MoveForward, ETriggerEvent::Triggered, this, &AEldenPlayerCharacter::MoveForward);

	enhancedInputComponent->BindAction(ia_MoveForward, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::MoveForward);

	enhancedInputComponent->BindAction(ia_MoveRight, ETriggerEvent::Triggered, this, &AEldenPlayerCharacter::MoveRight);

	enhancedInputComponent->BindAction(ia_MoveRight, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::MoveRight);

}

void AEldenPlayerCharacter::MoveForward(const FInputActionValue& val)
{
	x = val.Get<float>();
	direction.X = x;
}

void AEldenPlayerCharacter::MoveRight(const FInputActionValue& val)
{
	y = val.Get<float>();
	direction.Y = y;
}

void AEldenPlayerCharacter::Horizontal(const FInputActionValue& val)
{
	
}

void AEldenPlayerCharacter::Vertical(const FInputActionValue& val)
{

}

