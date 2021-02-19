// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonTestCharacter.h"

#include "AttributeSet.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Utils.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/Attributes/AttributeSetHealth.h"

//////////////////////////////////////////////////////////////////////////
// AThirdPersonTestCharacter

void AThirdPersonTestCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestCharacter::BeginPlay %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AThirdPersonTestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestCharacter::PossessedBy character: %s possessed by player controller: %s"), *GetName(), *NewController->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

void AThirdPersonTestCharacter::UnPossessed()
{
	if(GetWorld()->IsServer())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}
	auto controller = GetController();
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestCharacter::UnPossessed possessed by %s"), *controller->GetName());
	
	Super::UnPossessed();
	
	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestCharacter::UnPossessed %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
}

AThirdPersonTestCharacter::AThirdPersonTestCharacter()
{
	if(HasAuthority())
	{
		UE_LOG(LogTemp, Error, TEXT("SERVER:"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CLIENT:"));
	}

	UE_LOG(LogTemp, Warning, TEXT("AThirdPersonTestCharacter::AThirdPersonTestCharacter %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Role: %s Remote Role: %s"), *TransformRoleToFString(GetLocalRole()), *TransformRoleToFString(GetRemoteRole()));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThirdPersonTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AThirdPersonTestCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AThirdPersonTestCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AThirdPersonTestCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AThirdPersonTestCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AThirdPersonTestCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AThirdPersonTestCharacter::OnResetVR);
}


void AThirdPersonTestCharacter::OnResetVR()
{
	// If ThirdPersonTest is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in ThirdPersonTest.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AThirdPersonTestCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AThirdPersonTestCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AThirdPersonTestCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonTestCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AThirdPersonTestCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AThirdPersonTestCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}