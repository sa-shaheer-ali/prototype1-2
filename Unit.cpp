// #include "Unit.h"
// #include "DrawDebugHelpers.h"
// #include "Kismet/GameplayStatics.h"

// AUnit::AUnit()
// {
//     PrimaryActorTick.bCanEverTick = true;

//     // Initialize unit properties
//     Health = 100.0f;
//     MaxHealth = 100.0f;
//     AttackDamage = 10.0f;
//     AttackRange = 200.0f;
//     AttackCooldown = 1.0f;
//     TimeSinceLastAttack = 0.0f;
//     CurrentTarget = nullptr;
//     bIsSelected = false;
//     bIsMoving = false;
//     FormationOffset = FVector::ZeroVector;
// }

// void AUnit::BeginPlay()
// {
//     Super::BeginPlay();
// }

// void AUnit::Tick(float DeltaTime)
// {
//     Super::Tick(DeltaTime);

//     // Update combat
//     UpdateCombat(DeltaTime);

//     // Auto-detect enemies if we don't have a target
//     if (!CurrentTarget)
//     {
//         // Find closest enemy within range
//         TArray<AActor*> FoundActors;
//         UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), FoundActors);

//         float ClosestDistance = AttackRange;
//         AUnit* ClosestEnemy = nullptr;

//         for (AActor* Actor : FoundActors)
//         {
//             if (AUnit* PotentialTarget = Cast<AUnit>(Actor))
//             {
//                 // Don't target self or dead units
//                 if (PotentialTarget != this && PotentialTarget->Health > 0)
//                 {
//                     float Distance = FVector::Distance(GetActorLocation(), PotentialTarget->GetActorLocation());
//                     if (Distance < ClosestDistance)
//                     {
//                         ClosestDistance = Distance;
//                         ClosestEnemy = PotentialTarget;
//                     }
//                 }
//             }
//         }

//         // If we found an enemy in range, attack it
//         if (ClosestEnemy)
//         {
//             Attack(ClosestEnemy);
//         }
//     }

//     // Update formation position if moving
//     if (bIsMoving)
//     {
//         UpdateFormationPosition();
//     }

//     // Draw selection circle if selected
//     if (bIsSelected)
//     {
//         DrawDebugCircle(
//             GetWorld(),
//             GetActorLocation(),
//             100.0f,
//             32,
//             FColor::Green,
//             false,
//             -1.0f,
//             0,
//             2.0f
//         );
//     }
// }

// void AUnit::SetSelected(bool bSelected)
// {
//     bIsSelected = bSelected;
// }

// void AUnit::Attack(AUnit* Target)
// {
//     if (CanAttackTarget(Target))
//     {
//         CurrentTarget = Target;
//         TimeSinceLastAttack = 0.0f;
//     }
// }

// void AUnit::AttackMove(const FVector& Location)
// {
//     TargetLocation = Location;
//     bIsMoving = true;
//     CurrentTarget = nullptr;
// }

// void AUnit::UpdateFormationPosition()
// {
//     if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
//     {
//         FVector FormationLocation = TargetLocation + FormationOffset;
//         FVector Direction = (FormationLocation - GetActorLocation()).GetSafeNormal();
        
//         // Move towards formation position
//         AddMovementInput(Direction, 1.0f);
        
//         // Make unit face movement direction
//         if (!Direction.IsZero())
//         {
//             FRotator TargetRotation = Direction.Rotation();
//             SetActorRotation(TargetRotation);
//         }

//         // Check if we've reached the formation position
//         float DistanceToTarget = FVector::Distance(GetActorLocation(), FormationLocation);
//         if (DistanceToTarget < 100.0f)
//         {
//             bIsMoving = false;
//             MovementComp->Velocity = FVector::ZeroVector;
//         }
//     }
// }

// bool AUnit::CanAttackTarget(AUnit* Target) const
// {
//     if (!Target || Target->Health <= 0.0f)
//         return false;

//     float DistanceToTarget = FVector::Distance(GetActorLocation(), Target->GetActorLocation());
//     return DistanceToTarget <= AttackRange;
// }

// void AUnit::UpdateCombat(float DeltaTime)
// {
//     if (CurrentTarget && CanAttackTarget(CurrentTarget))
//     {
//         TimeSinceLastAttack += DeltaTime;
//         if (TimeSinceLastAttack >= AttackCooldown)
//         {
//             // Deal damage to target
//             CurrentTarget->Health = FMath::Max(0.0f, CurrentTarget->Health - AttackDamage);
//             TimeSinceLastAttack = 0.0f;

//             // Draw debug line to show attack
//             DrawDebugLine(
//                 GetWorld(),
//                 GetActorLocation(),
//                 CurrentTarget->GetActorLocation(),
//                 FColor::Red,
//                 false,
//                 0.1f,
//                 0,
//                 1.0f
//             );

//             // Clear target if dead
//             if (CurrentTarget->Health <= 0.0f)
//             {
//                 CurrentTarget = nullptr;
//             }
//         }
//     }
//     else
//     {
//         CurrentTarget = nullptr;
//     }
// } 