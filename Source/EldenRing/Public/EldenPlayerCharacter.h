// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EldenPlayerCharacter.generated.h"

UCLASS()
class ELDENRING_API AEldenPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEldenPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_Horizontal;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_Vertical;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_MoveForward;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_MoveRight;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
		class UInputAction* ia_Spacebar;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_S;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_SReleased;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_FPressed;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_MPressed;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputAction* ia_MReleased;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	class UInputMappingContext* imc_myMapping;

	UPROPERTY(EditDefaultsOnly, Category = playerSettings)
	float rollingDestance = 1500;

private:

	UFUNCTION(BlueprintCallable)
	void MoveForward(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable)
	void MoveRight(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable)
	void Horizontal(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable)
	void Vertical(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable)
	void Rolling();

	UFUNCTION(BlueprintCallable)
	void SPressed();
	
	UFUNCTION(BlueprintCallable)
	void SRelease();

	UFUNCTION(BlueprintCallable)
	void Jumping();

	UFUNCTION(BlueprintCallable)
	void OpenMap();

	UFUNCTION(BlueprintCallable)
	void CloseMap();

	UPROPERTY()
	FVector direction;

	float x;
	float y;
	float h;
	float v;

	bool isSPressed=false;
	bool isMapOpen = false;
};
