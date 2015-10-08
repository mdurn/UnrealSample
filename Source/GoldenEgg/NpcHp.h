// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "NpcHp.generated.h"

class ANPC;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOLDENEGG_API UNpcHp : public UActorComponent
{
  GENERATED_BODY()
  const ANPC* npc;

public:
	// Sets default values for this component's properties
	UNpcHp();
  
  bool is_visible;
  
  UPROPERTY(EditAnywhere, Category = Health)
  int32 max_hp;
  
  UPROPERTY(EditAnywhere, Category = Health)
  int32 current_hp;
  
  FVector2D GetScreenPosition();

  void InitHp(int32 max_hp_, int32 current_hp_);
  
  void SetNpc(const ANPC* npc_);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
};
