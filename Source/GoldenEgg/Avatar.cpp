// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "Avatar.h"
#include "PickupItem.h"
#include "NPC_HUD.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
  InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
  InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}


void AAvatar::MoveForward(float amount)
{
  if (inventory_showing) { return; }
  
	if (Controller && amount)
	{
		FVector forward = GetActorForwardVector();
		AddMovementInput(forward, amount);
	}
}

void AAvatar::MoveRight(float amount)
{
  if (inventory_showing) { return; }
  
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}

}

void AAvatar::Yaw(float amount)
{
  if (inventory_showing) {
    APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
    ANPC_HUD* hud = Cast<ANPC_HUD>(p_controller->GetHUD());
    hud->MouseMoved();
    return;
  } else {
  	AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
  }
}

void AAvatar::Pitch(float amount)
{
  if (inventory_showing) {
    APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
    ANPC_HUD* hud = Cast<ANPC_HUD>(p_controller->GetHUD());
    hud->MouseMoved();
    return;
  } else {
    AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
  }
}

void AAvatar::ToggleInventory()
{
  APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
  ANPC_HUD* hud = Cast<ANPC_HUD>(p_controller->GetHUD());
  
  if (inventory_showing) {
    hud->ClearWidgets();
    inventory_showing = false;
    p_controller->bShowMouseCursor = false;
    return;
  }
  
  inventory_showing = true;
  p_controller->bShowMouseCursor = true;
  for (TMap<FString, int>::TIterator it = backpack.CreateIterator(); it; ++it) {
    FString fs = it->Key + FString::Printf(TEXT(" x %d"), it->Value);
    UTexture2D* tex;
    if (icons.Find(it->Key)) {
      tex = icons[it->Key];
      hud->AddWidget(Widget(Icon(fs, tex)));
    }
  }
}

void AAvatar::Pickup(APickupItem* item)
{
  if (backpack.Find(item->name))
  {
    backpack[item->name] += item->quantity;
  } else {
    backpack.Add(item->name, item->quantity);
    icons.Add(item->name, item->icon);
  }
}

void AAvatar::MouseClicked() {
  APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
  ANPC_HUD* hud = Cast<ANPC_HUD>(p_controller->GetHUD());
  hud->MouseClicked();
}
