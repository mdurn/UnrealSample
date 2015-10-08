// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "PickupItem.h"
#include "Avatar.h"
#include "NPC_HUD.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

APickupItem::APickupItem(const class FObjectInitializer& OI) : Super(OI)
{
  name = "UNKNOWN ITEM";
  quantity = 0;
  
  prox_sphere = OI.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
  mesh = OI.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
  
  RootComponent = mesh;
  mesh->SetSimulatePhysics(true);
  
  prox_sphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
  prox_sphere->AttachTo(mesh);
}

void APickupItem::Prox_Implementation(AActor* other_actor, UPrimitiveComponent* other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult &sweep_result) {
  if (Cast<AAvatar>(other_actor) == nullptr) { return; }
  
  AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  
  avatar->Pickup(this);
  
  APlayerController* p_controller = GetWorld()->GetFirstPlayerController();
  
  ANPC_HUD* hud = Cast<ANPC_HUD>(p_controller->GetHUD());
  hud->AddMessage(Message(FString("Picked up ") + FString::FromInt(quantity) + FString(" ") + name, 5.f, FColor::White, icon));
  
  Destroy();
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

