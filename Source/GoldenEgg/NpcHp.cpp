// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "NpcHp.h"
#include "NPC.h"


// Sets default values for this component's properties
UNpcHp::UNpcHp() {
  is_visible = false;
  max_hp = current_hp = 100;
}


// Called when the game starts
void UNpcHp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNpcHp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

FVector2D UNpcHp::GetScreenPosition() {
  FVector origin, box_extent;
  FVector actor_top;
  FVector2D screen_pos;
  bool valid = false;
  
  UCapsuleComponent* capsule = npc->GetCapsuleComponent();
  npc->GetActorBounds(true, origin, box_extent);
  actor_top = FVector(origin.X, origin.Y, origin.Z + capsule->GetScaledCapsuleHalfHeight());
  
  APlayerController* p_controller = npc->GetWorld()->GetFirstPlayerController();
  
  if (p_controller)
  {
    valid = p_controller->ProjectWorldLocationToScreen(actor_top, screen_pos);
  }
  
  if (valid) {
    return screen_pos;
  } else {
    return FVector2D(-1.f, -1.f);
  }
}

void UNpcHp::InitHp(int32 max_hp_, int32 current_hp_) {
  max_hp = max_hp_;
  current_hp = current_hp_;
}

void UNpcHp::SetNpc(const ANPC* npc_) {
  npc = npc_;
}
