// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "NPC.h"
#include "Avatar.h"
#include "NPC_HUD.h"
#include "NpcHp.h"

// Sets default values
ANPC::ANPC(const class FObjectInitializer& OI) : Super(OI)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  ProxSphere = OI.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));
  ProxSphere->AttachTo(RootComponent);
  ProxSphere->SetSphereRadius(160.f);
  ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
  ProxSphere->OnComponentEndOverlap.AddDynamic(this, &ANPC::ProxEnd);
  NPCMessage = "I am an NPC.";
  Name = "Guy";
  hp = OI.CreateDefaultSubobject<UNpcHp>(this, TEXT("HP"));
  InitHp(100, 100);
}

void ANPC::InitHp(int32 max_hp, int32 current_hp) {
  hp->InitHp(max_hp, current_hp);
  hp->SetNpc(this);
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if (Cast<AAvatar>(OtherActor) == nullptr) { return; }
  
  APlayerController* PController = GetWorld()->GetFirstPlayerController();
  
  if (PController)
  {
    ANPC_HUD* hud = Cast<ANPC_HUD>(PController->GetHUD());
    FString NameAndMessage = FString::Printf(TEXT("%s: %s"), *Name, *NPCMessage);
    hud->AddMessage(Message(NameAndMessage, 5.f, FColor::White, Face));
    hp->is_visible = true;
    hud->AddHpBar(hp);
  }
}

void ANPC::ProxEnd_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
  if (Cast<AAvatar>(OtherActor) == nullptr) { return; }
  hp->is_visible = false;
}

// Called every frame
void ANPC::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
