// Fill out your copyright notice in the Description page of Project Settings.


#include "EldenPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values
AEldenPlayerCharacter::AEldenPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));

	GetCharacterMovement();
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

	direction.Z = 0;
	direction.Normalize();

	AddMovementInput(direction);
	direction = FVector::ZeroVector;
	//UE_LOG(LogTemp, Warning, TEXT("ad"));
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

	enhancedInputComponent->BindAction(ia_Spacebar, ETriggerEvent::Started, this, &AEldenPlayerCharacter::Rolling);
	//S 버튼이 눌렸는지 검사하는 함수
	enhancedInputComponent->BindAction(ia_S, ETriggerEvent::Started, this, &AEldenPlayerCharacter::SPressed);
	enhancedInputComponent->BindAction(ia_SReleased, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::SRelease);

	//F jump
	enhancedInputComponent->BindAction(ia_FPressed, ETriggerEvent::Started, this, &AEldenPlayerCharacter::Jumping);

	//M map open
	enhancedInputComponent->BindAction(ia_MPressed, ETriggerEvent::Started, this, &AEldenPlayerCharacter::OpenMap);
	//enhancedInputComponent->BindAction(ia_MReleased, ETriggerEvent::Completed, this, &AEldenPlayerCharacter::CloseMap);




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
	
	h = val.Get<float>();
	AddControllerYawInput(h);

}

void AEldenPlayerCharacter::Vertical(const FInputActionValue& val)
{

	v = val.Get<float>();
	AddControllerPitchInput(v);

}

void AEldenPlayerCharacter::Rolling()
{
	if (isSPressed == false) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Rolling")));
	}
	else if(isSPressed == true) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("BackStep")));
	}
}

void AEldenPlayerCharacter::SPressed()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("true")));
	isSPressed = true;
}

void AEldenPlayerCharacter::SRelease()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("false")));
	isSPressed = false;
}

void AEldenPlayerCharacter::Jumping()
{
	Jump();
}

void AEldenPlayerCharacter::OpenMap()
{
	if (isMapOpen == false) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("MapOpen")));
		isMapOpen = true;
	}
	else if (isMapOpen == true) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("MapClosed")));
		isMapOpen = false;
	}


}

void AEldenPlayerCharacter::CloseMap()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CloseMap")));
}

