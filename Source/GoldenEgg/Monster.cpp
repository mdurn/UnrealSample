// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "Monster.h"
#include "Avatar.h"
#include "MeleeWeapon.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMonster::AMonster(const class FObjectInitializer& PCIP) : Super(PCIP)
{
  Speed = 20;
  HitPoints = 20;
  Experience = 0;
  BPLoot = NULL;
  BaseAttackDamage = 1;
  AttackTimeout = 1.5f;
  TimeSinceLastStrike = 0;
  SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
  SightSphere->AttachTo( RootComponent );
  AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
  AttackRangeSphere->AttachTo( RootComponent );
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaSeconds)
{
  Super::Tick( DeltaSeconds );
  AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  if( !avatar ) return;
  FVector toPlayer = avatar->GetActorLocation() -  GetActorLocation();
  float distanceToPlayer = toPlayer.Size();
  // If the player is not in the SightSphere of the monster,
  // go back
  if( !isInSightRange(distanceToPlayer) )
  {
    // If the player is out of sight,
    // then the enemy cannot chase
    return;
  }
  
  toPlayer.Normalize(); // reduce to unit vector
  // Actually move the monster towards the player a bit
  AddMovementInput(toPlayer, Speed*DeltaSeconds);
  // At least face the target
  // Gets you the rotator to turn something
  // that looks in the `toPlayer` direction
  FRotator toPlayerRotation = toPlayer.Rotation();
  toPlayerRotation.Pitch = 0; // 0 off the pitch
  RootComponent->SetWorldRotation( toPlayerRotation );
}

bool AMonster::IsInAttackRangeOfPlayer() {
  AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
  if( !avatar ) { return false; }
  
  FVector toPlayer = avatar->GetActorLocation() -  GetActorLocation();
  float distanceToPlayer = toPlayer.Size();
  return isInAttackRange(distanceToPlayer);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMonster::PostInitializeComponents()
{
  Super::PostInitializeComponents();
  // instantiate the melee weapon if a bp was selected
  if( BPMeleeWeapon )
  {
    MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>( BPMeleeWeapon, FVector(), FRotator() );
    if( MeleeWeapon )
    {
      const USkeletalMeshSocket *socket = Mesh->GetSocketByName("RightHandSocket" );
      // be sure to use correct
      // socket name!
      socket->AttachActor( MeleeWeapon, Mesh );
    }
  }
}
