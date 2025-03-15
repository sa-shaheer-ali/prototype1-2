#include "RTS_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "DrawDebugHelpers.h"

ARTS_PlayerController::ARTS_PlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
    bIsSelecting = false;
    PrimaryActorTick.bCanEverTick = true;  // Enable tick
}

void ARTS_PlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Find the UnitController in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnitController::StaticClass(), FoundActors);
    if (FoundActors.Num() > 0)
    {
        UnitController = Cast<AUnitController>(FoundActors[0]);
    }
}

void ARTS_PlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsSelecting)
    {
        DrawSelectionBox();
    }
}

void ARTS_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // Bind mouse inputs
    InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ARTS_PlayerController::OnLeftMouseButtonPressed);
    InputComponent->BindAction("LeftMouseButton", IE_Released, this, &ARTS_PlayerController::OnLeftMouseButtonReleased);
    InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &ARTS_PlayerController::OnRightMouseButtonPressed);

    // Bind mouse movement with axis values
    InputComponent->BindAxis("MouseX", this, &ARTS_PlayerController::OnMouseMoveX);
    InputComponent->BindAxis("MouseY", this, &ARTS_PlayerController::OnMouseMoveY);
}

void ARTS_PlayerController::OnLeftMouseButtonPressed()
{
    if (!UnitController)
        return;

    bIsSelecting = true;
    GetMousePosition(SelectionStart.X, SelectionStart.Y);
    UnitController->StartSelection(SelectionStart);
}

void ARTS_PlayerController::OnLeftMouseButtonReleased()
{
    if (!UnitController)
        return;

    bIsSelecting = false;
    UnitController->EndSelection();
}

void ARTS_PlayerController::OnRightMouseButtonPressed()
{
    if (!UnitController)
        return;

    // Get world location under mouse cursor
    FVector WorldLocation;
    if (GetMousePositionInWorld(WorldLocation))
    {
        // Move selected units to clicked location
        UnitController->MoveSelectedUnitsTo(WorldLocation);
    }
}

void ARTS_PlayerController::OnMouseMoveX(float Value)
{
    UpdateSelection();
}

void ARTS_PlayerController::OnMouseMoveY(float Value)
{
    UpdateSelection();
}

void ARTS_PlayerController::UpdateSelection()
{
    if (!UnitController || !bIsSelecting)
        return;

    FVector2D CurrentMousePos;
    GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);
    UnitController->UpdateSelection(CurrentMousePos);
}

void ARTS_PlayerController::DrawSelectionBox()
{
    if (!bIsSelecting)
        return;

    FVector2D CurrentMousePos;
    GetMousePosition(CurrentMousePos.X, CurrentMousePos.Y);

    // Draw the selection box using debug lines in world space
    FVector WorldStart, WorldStartDir;
    FVector WorldEnd, WorldEndDir;
    
    DeprojectScreenPositionToWorld(SelectionStart.X, SelectionStart.Y, WorldStart, WorldStartDir);
    DeprojectScreenPositionToWorld(CurrentMousePos.X, CurrentMousePos.Y, WorldEnd, WorldEndDir);

    // Perform line traces to find ground points
    FHitResult HitStart, HitEnd;
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = false;

    GetWorld()->LineTraceSingleByChannel(HitStart, WorldStart, WorldStart + WorldStartDir * 10000.0f, ECC_Visibility, QueryParams);
    GetWorld()->LineTraceSingleByChannel(HitEnd, WorldEnd, WorldEnd + WorldEndDir * 10000.0f, ECC_Visibility, QueryParams);

    if (HitStart.bBlockingHit && HitEnd.bBlockingHit)
    {
        // Draw debug box in world space
        FVector BoxCenter = (HitStart.Location + HitEnd.Location) * 0.5f;
        FVector BoxExtent = (HitEnd.Location - HitStart.Location).GetAbs() * 0.5f;
        BoxExtent.Z = 100.0f;  // Height of selection box

        DrawDebugBox(
            GetWorld(),
            BoxCenter,
            BoxExtent,
            FQuat::Identity,
            FColor::Green,
            false,
            -1.0f,
            0,
            2.0f
        );
    }
}

bool ARTS_PlayerController::GetMousePositionInWorld(FVector& OutLocation) const
{
    FVector WorldLocation, WorldDirection;
    if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
    {
        // Perform line trace to find ground
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.bTraceComplex = false;

        FVector EndLocation = WorldLocation + WorldDirection * 10000.0f;
        if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, EndLocation, ECC_Visibility, QueryParams))
        {
            OutLocation = HitResult.Location;
            return true;
        }
    }
    return false;
} 