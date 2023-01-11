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

	APlayerController* playerCon = Cast<APlayerController>(GetController());

	if (playerCon != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());


		if (subsys != nullptr) {
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}

}

// Called every frame
void AEldenPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//디렉션을 컨트롤러 방향으로 변환
	direction = FTransform(GetControlRotation()).TransformVector(direction); 
	AddMovementInput(direction);
	direction = FVector::ZeroVector;
	//UE_LOG(LogTemp, Warning, TEXT("ad"));
}

// Called to bind functionality to input
void AEldenPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ia_Horizontal, ETriggerEvent::Started, this, &AEldenPlayerCharacter::Horizontal);

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
	UE_LOG(LogTemp, Warning, TEXT("ws"));
	x = val.Get<float>();
	direction.X = x;
	UE_LOG(LogTemp, Warning, TEXT("ws"));
}

void AEldenPlayerCharacter::MoveRight(const FInputActionValue& val)
{
	UE_LOG(LogTemp, Warning, TEXT("ad"));
	y = val.Get<float>();
	direction.Y = y;
	UE_LOG(LogTemp, Warning, TEXT("ad"));
}

void AEldenPlayerCharacter::Horizontal(const FInputActionValue& val)
{
	UE_LOG(LogTemp, Warning, TEXT("h"));
	h = val.Get<float>();
	AddControllerYawInput(h);
	UE_LOG(LogTemp, Warning, TEXT("h"));
}

void AEldenPlayerCharacter::Vertical(const FInputActionValue& val)
{
	UE_LOG(LogTemp, Warning, TEXT("v"));
	v = val.Get<float>();
	AddControllerPitchInput(v);
	UE_LOG(LogTemp, Warning, TEXT("v"));
}

