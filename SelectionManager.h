// #pragma once

// #include "CoreMinimal.h"
// #include "GameFramework/Actor.h"
// #include "SelectionManager.generated.h"

// class AUnit;

// UCLASS()
// class PROTOTYPE1_API ASelectionManager : public AActor
// {
//     GENERATED_BODY()

// public:
//     ASelectionManager();

//     virtual void BeginPlay() override;
//     virtual void Tick(float DeltaTime) override;

//     // Selection functions
//     void StartSelection(const FVector2D& ScreenPos);
//     void UpdateSelection(const FVector2D& ScreenPos);
//     void EndSelection();
//     void AddToSelection(AUnit* Unit);
//     void RemoveFromSelection(AUnit* Unit);
//     void ClearSelection();

//     // Get selected units
//     const TArray<AUnit*>& GetSelectedUnits() const { return SelectedUnits; }

//     // Movement commands
//     void MoveSelectedUnits(const FVector& Location);
//     void AttackMoveSelectedUnits(const FVector& Location);

//     // Formation
//     void UpdateFormationOffsets();

// protected:
//     // Selection state
//     UPROPERTY(VisibleAnywhere, Category = "RTS|Selection")
//     FVector2D SelectionStart;

//     UPROPERTY(VisibleAnywhere, Category = "RTS|Selection")
//     FVector2D SelectionEnd;

//     UPROPERTY(VisibleAnywhere, Category = "RTS|Selection")
//     bool bIsSelecting;

//     // Selected units
//     UPROPERTY(VisibleAnywhere, Category = "RTS|Selection")
//     TArray<AUnit*> SelectedUnits;

//     // Formation settings
//     UPROPERTY(EditAnywhere, Category = "RTS|Formation")
//     float UnitSpacing;

//     UPROPERTY(EditAnywhere, Category = "RTS|Formation")
//     int32 UnitsPerRow;

// private:
//     // Helper functions
//     bool IsUnitInSelectionBox(AUnit* Unit) const;
//     void DrawSelectionBox() const;
//     FVector2D GetScreenPosition(const FVector& WorldLocation) const;
//     FVector GetWorldPosition(const FVector2D& ScreenLocation) const;
// }; 