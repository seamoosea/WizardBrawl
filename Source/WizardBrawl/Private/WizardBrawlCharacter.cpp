// Copyright Epic Games, Inc. All Rights Reserved.

#include "WizardBrawlCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "WBPlayerState.h"
#include "WBGameplayAbility.h"
#include "WizardBrawl.h"

AWizardBrawlCharacter::AWizardBrawlCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

    bool bIsDead = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWizardBrawlCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindASCInput();
}

class UAbilitySystemComponent* AWizardBrawlCharacter::GetAbilitySystemComponent() const
{
	AWBPlayerState* PS = GetPlayerState<AWBPlayerState>();
	if (PS) return PS->GetAbilitySystemComponent();
	return nullptr;
}


void AWizardBrawlCharacter::AcquireAbility(TSubclassOf<UWBGameplayAbility> AbilityToAcquire)
{
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("AbilityToAcquire: %d"), static_cast<int32>(AbilityToAcquire.GetDefaultObject()->AbilityInputID)));
	}
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && AbilityToAcquire)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire, 1, static_cast<int32>(AbilityToAcquire.GetDefaultObject()->AbilityInputID), this));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Success")));
		}
	}
}

void AWizardBrawlCharacter::AcquireAbilities(TArray<TSubclassOf<UWBGameplayAbility>> AbilitiesToAcquire)
{
    for(TSubclassOf<UWBGameplayAbility> AbilityItem : AbilitiesToAcquire)
    {
        AcquireAbility(AbilityItem);
    }
}



void AWizardBrawlCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AWBPlayerState* PS = GetPlayerState<AWBPlayerState>();
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (PS && AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}
}

void AWizardBrawlCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AWBPlayerState* PS = GetPlayerState<AWBPlayerState>();
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (PS && AbilitySystemComponent) {
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	}

	BindASCInput();
}

void AWizardBrawlCharacter::AddGameplayTag(FGameplayTag& TagToAdd)
{
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (AbilitySystemComponent) {
		GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
		GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
	}
}

void AWizardBrawlCharacter::RemoveGameplayTag(FGameplayTag& TagToRemove)
{
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (AbilitySystemComponent) {
		AbilitySystemComponent->RemoveLooseGameplayTag(TagToRemove);
	}
}


void AWizardBrawlCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AWizardBrawlCharacter::BindASCInput()
{
	UWBAbilitySystemComponent* AbilitySystemComponent = Cast<UWBAbilitySystemComponent>(GetAbilitySystemComponent());
	if (AbilitySystemComponent && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("EGDAbilityInputID"), static_cast<int32>(EWBAbilityInputID::Confirm), static_cast<int32>(EWBAbilityInputID::Cancel)));
	}
}
