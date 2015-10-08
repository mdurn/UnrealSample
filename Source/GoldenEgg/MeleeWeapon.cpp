// Fill out your copyright notice in the Description page of Project Settings.

#include "GoldenEgg.h"
#include "MeleeWeapon.h"
#include "Monster.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMeleeWeapon::AMeleeWeapon(const class FObjectInitializer& PCIP) : Super(PCIP)
{
  AttackDamage = 1;
  Swinging = false;
  WeaponHolder = NULL;
  Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
  RootComponent = Mesh;
  ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
  ProxBox->OnComponentBeginOverlap.AddDynamic( this,  &AMeleeWeapon::Prox );
  ProxBox->AttachTo( RootComponent );
}

void AMeleeWeapon::Prox_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool  bFromSweep, const FHitResult & SweepResult )
{
  // don't hit non root components
  if( OtherComp != OtherActor->GetRootComponent() ) { return; }
  
  // avoid hitting things while sword isn't swinging,
  // avoid hitting yourself, and
  // avoid hitting the same OtherActor twice
  if( Swinging && Cast<AMonster>(OtherActor) != WeaponHolder && !ThingsHit.Contains(OtherActor) )
  {
    OtherActor->TakeDamage( AttackDamage + WeaponHolder->BaseAttackDamage, FDamageEvent(), NULL, this );
    ThingsHit.Add( OtherActor );
  }
}

void AMeleeWeapon::Swing()
{
  ThingsHit.Empty();  // empty the list
  Swinging = true;
}

void AMeleeWeapon::Rest()
{
  ThingsHit.Empty();
  Swinging = false;
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

