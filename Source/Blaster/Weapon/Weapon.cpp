// Copyright Fedahumada


#include "Weapon.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Blaster/Characters/BlasterCharacter.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(GetRootComponent());
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
		AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnSphereEndOverlap);
	}
	if (PickupWidget) {
		PickupWidget->SetVisibility(false);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeapon, WeaponState);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OvelappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter) {
		BlasterCharacter->SetOverlappinWeapon(this);
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OvelappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (BlasterCharacter) {
		BlasterCharacter->SetOverlappinWeapon(nullptr);
	}
}

void AWeapon::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget) {
		PickupWidget->SetVisibility(bShowWidget);
	}
}

void AWeapon::SetWeaponState(EWeaponState State)
{
	WeaponState = State;
	switch (WeaponState) {
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		GetAreaSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	}
}

void AWeapon::OnRep_WeaponState()
{
	switch (WeaponState) {
	case EWeaponState::EWS_Equipped:
		ShowPickupWidget(false);
		break;
	}
}
