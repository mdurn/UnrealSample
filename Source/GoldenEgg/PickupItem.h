// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class GOLDENEGG_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:
  APickupItem(const class FObjectInitializer& OI);
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
  FString name;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
  int32 quantity;
  
  UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
  USphereComponent* prox_sphere;
  
  UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)
  UStaticMeshComponent* mesh;
  
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
  UTexture2D* icon;
  
  UFUNCTION(BlueprintNativeEvent, Category = Collision)
  void Prox(AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult &sweep_result);
  
	// Sets default values for this actor's properties
	APickupItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
