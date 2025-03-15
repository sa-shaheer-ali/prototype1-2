#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnitController.h"
#include "RTS_PlayerController.generated.h"

UCLASS()
class PROTOTYPE1_API ARTS_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ARTS_PlayerController();

    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

protected:
    virtual void SetupInputComponent() override;

    // Selection variables
    UPROPERTY()
    bool bIsSelecting;
    UPROPERTY()
    FVector2D SelectionStart;

    // Input functions
    void OnLeftMouseButtonPressed();
    void OnLeftMouseButtonReleased();
    void OnRightMouseButtonPressed();
    void OnMouseMoveX(float Value);
    void OnMouseMoveY(float Value);

    // Helper functions
    void UpdateSelection();
    void DrawSelectionBox();
    bool GetMousePositionInWorld(FVector& OutLocation) const;

    // Reference to UnitController
    UPROPERTY()
    AUnitController* UnitController;
};