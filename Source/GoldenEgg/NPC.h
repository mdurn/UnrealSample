// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"

class UNpcHp;

UCLASS()
class GOLDENEGG_API ANPC : public ACharacter
{
	GENERATED_UCLASS_BODY()
  
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
  FString NPCMessage;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCMessage)
  UTexture2D* Face;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
  FString Name;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Details")
  UNpcHp* hp;
  
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
  USphereComponent* ProxSphere;
  
  UFUNCTION(BlueprintNativeEvent, Category = Collision)
  void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
  
  UFUNCTION(BlueprintNativeEvent, Category = Collision)
  void ProxEnd(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
  
  UFUNCTION()
  void InitHp(int32 max_hp, int32 current_hp);
};
