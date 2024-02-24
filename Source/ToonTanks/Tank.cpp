// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

ATank::ATank() 
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    CurrentSpeed = SetSpeed;

}



void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

    //Calls the parent class function of the Setup Player Input Component 
    Super::SetupPlayerInputComponent(PlayerInputComponent);


        PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

        PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

        PlayerInputComponent->BindAxis(TEXT("Dash"), this, &ATank::Dash);

        PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}


void ATank::HandleDestruction(){


    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    TankPlayerController = Cast<APlayerController>(GetController());
    bPaused = TankPlayerController->SetPause(false);
}


void ATank::Move(float Value) 
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value;
    Speed = Value;

    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);


    //Apple Deltatime so the movement is independant of the tick
    DeltaLocation = CurrentSpeed * DeltaLocation * DeltaTime;


    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) 
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    //UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), Speed);
    //Implement the Rotation Rate: Yaw = Value * DeltaTime * TurnRate

    if (Speed < 0) {
        DeltaRotation.Yaw = -Value * DeltaTime * TurnRate;

    } else {

        DeltaRotation.Yaw = Value * DeltaTime * TurnRate;
    }

    AddActorLocalRotation(DeltaRotation,true);

}


void ATank::Dash(float Value)
{
    

    if (Value == 1.0) {

        CurrentSpeed = FMath::Lerp(CurrentSpeed, MaxSpeed, Acceleration);

    } else {

        CurrentSpeed = SetSpeed;

    }
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TankPlayerController) {

        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

    RotateTurret(HitResult.ImpactPoint);
    }
}

void ATank::Fire(){

    if (Ammo > 0) {

        Super::Fire();
        Ammo = Ammo - 1;
    }


} 

void ATank::RecoverAmmo(float Value) {

    Ammo = Ammo + Value;

    if (Ammo > MaxAmmo) {
        Ammo = MaxAmmo;
    }
}

float ATank::GetAmmoValue() const {

    return Ammo;
}

float ATank::GetMaxAmmoValue() const {

    return MaxAmmo;
}