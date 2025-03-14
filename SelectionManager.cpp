// #include "SelectionManager.h"
// #include "Unit.h"
// #include "DrawDebugHelpers.h"
// #include "Kismet/GameplayStatics.h"
// #include "GameFramework/PlayerController.h"

// ASelectionManager::ASelectionManager()
// {
//     PrimaryActorTick.bCanEverTick = true;

//     // Initialize selection state
//     bIsSelecting = false;
//     SelectionStart = FVector2D::ZeroVector;
//     SelectionEnd = FVector2D::ZeroVector;

//     // Initialize formation settings
//     UnitSpacing = 150.0f;
//     UnitsPerRow = 5;
// }

// void ASelectionManager::BeginPlay()
// {
//     Super::BeginPlay();
// }

// void ASelectionManager::Tick(float DeltaTime)
// {
//     Super::Tick(DeltaTime);

//     // Draw selection box while selecting
//     if (bIsSelecting)
//     {
//         DrawSelectionBox();
//     }
// }

// void ASelectionManager::StartSelection(const FVector2D& ScreenPos)
// {
//     bIsSelecting = true;
//     SelectionStart = ScreenPos;
//     SelectionEnd = ScreenPos;
// }

// void ASelectionManager::UpdateSelection(const FVector2D& ScreenPos)
// {
//     if (bIsSelecting)
//     {
//         SelectionEnd = ScreenPos;
//     }
// }

// void ASelectionManager::EndSelection()
// {
//     if (bIsSelecting)
//     {
//         bIsSelecting = false;

//         // Get all units in the world
//         TArray<AActor*> FoundActors;
//         UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), FoundActors);

//         // Clear current selection
//         ClearSelection();

//         // Select units in the selection box
//         for (AActor* Actor : FoundActors)
//         {
//             if (AUnit* Unit = Cast<AUnit>(Actor))
//             {
//                 if (IsUnitInSelectionBox(Unit))
//                 {
//                     AddToSelection(Unit);
//                 }
//             }
//         }

//         // Update formation offsets for selected units
//         UpdateFormationOffsets();
//     }
// }

// void ASelectionManager::AddToSelection(AUnit* Unit)
// {
//     if (Unit && !SelectedUnits.Contains(Unit))
//     {
//         SelectedUnits.Add(Unit);
//         Unit->SetSelected(true);
//     }
// }

// void ASelectionManager::RemoveFromSelection(AUnit* Unit)
// {
//     if (Unit && SelectedUnits.Remove(Unit) > 0)
//     {
//         Unit->SetSelected(false);
//     }
// }

// void ASelectionManager::ClearSelection()
// {
//     for (AUnit* Unit : SelectedUnits)
//     {
//         if (Unit)
//         {
//             Unit->SetSelected(false);
//         }
//     }
//     SelectedUnits.Empty();
// }

// void ASelectionManager::MoveSelectedUnits(const FVector& Location)
// {
//     for (AUnit* Unit : SelectedUnits)
//     {
//         if (Unit)
//         {
//             Unit->MoveToLocation(Location);
//         }
//     }
// }

// void ASelectionManager::AttackMoveSelectedUnits(const FVector& Location)
// {
//     for (AUnit* Unit : SelectedUnits)
//     {
//         if (Unit)
//         {
//             Unit->AttackMove(Location);
//         }
//     }
// }

// void ASelectionManager::UpdateFormationOffsets()
// {
//     for (int32 i = 0; i < SelectedUnits.Num(); ++i)
//     {
//         if (AUnit* Unit = SelectedUnits[i])
//         {
//             // Calculate grid position
//             int32 Row = i / UnitsPerRow;
//             int32 Col = i % UnitsPerRow;

//             // Calculate offset
//             FVector Offset(
//                 Col * UnitSpacing,
//                 Row * UnitSpacing,
//                 0.0f
//             );

//             // Apply offset
//             Unit->FormationOffset = Offset;
//         }
//     }
// }

// bool ASelectionManager::IsUnitInSelectionBox(AUnit* Unit) const
// {
//     if (!Unit)
//         return false;

//     FVector2D UnitScreenPos = GetScreenPosition(Unit->GetActorLocation());

//     // Calculate selection box bounds
//     float MinX = FMath::Min(SelectionStart.X, SelectionEnd.X);
//     float MaxX = FMath::Max(SelectionStart.X, SelectionEnd.X);
//     float MinY = FMath::Min(SelectionStart.Y, SelectionEnd.Y);
//     float MaxY = FMath::Max(SelectionStart.Y, SelectionEnd.Y);

//     // Check if unit is within bounds
//     return UnitScreenPos.X >= MinX && UnitScreenPos.X <= MaxX &&
//            UnitScreenPos.Y >= MinY && UnitScreenPos.Y <= MaxY;
// }

// void ASelectionManager::DrawSelectionBox() const
// {
//     // Get screen positions
//     FVector2D Start = SelectionStart;
//     FVector2D End = SelectionEnd;

//     // Draw selection box
//     DrawDebugLine(
//         GetWorld(),
//         GetWorldPosition(Start),
//         GetWorldPosition(FVector2D(End.X, Start.Y)),
//         FColor::Yellow,
//         false,
//         -1.0f,
//         0,
//         2.0f
//     );

//     DrawDebugLine(
//         GetWorld(),
//         GetWorldPosition(FVector2D(End.X, Start.Y)),
//         GetWorldPosition(End),
//         FColor::Yellow,
//         false,
//         -1.0f,
//         0,
//         2.0f
//     );

//     DrawDebugLine(
//         GetWorld(),
//         GetWorldPosition(End),
//         GetWorldPosition(FVector2D(Start.X, End.Y)),
//         FColor::Yellow,
//         false,
//         -1.0f,
//         0,
//         2.0f
//     );

//     DrawDebugLine(
//         GetWorld(),
//         GetWorldPosition(FVector2D(Start.X, End.Y)),
//         GetWorldPosition(Start),
//         FColor::Yellow,
//         false,
//         -1.0f,
//         0,
//         2.0f
//     );
// }

// FVector2D ASelectionManager::GetScreenPosition(const FVector& WorldLocation) const
// {
//     APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//     if (PC)
//     {
//         FVector2D ScreenPos;
//         PC->ProjectWorldLocationToScreen(WorldLocation, ScreenPos);
//         return ScreenPos;
//     }
//     return FVector2D::ZeroVector;
// }

// FVector ASelectionManager::GetWorldPosition(const FVector2D& ScreenLocation) const
// {
//     APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//     if (PC)
//     {
//         FVector WorldLocation, WorldDirection;
//         PC->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
//         return WorldLocation;
//     }
//     return FVector::ZeroVector;
// } 