#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

/// <summary>
/// Implemented
/// </summary>
Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors

  // Default to 0
  if (neighborhood.empty()) 
      return Vector2f::zero();

  Vector2f averageVelocity = Vector2f::zero();

  for (Boid* neighbor : neighborhood)
    averageVelocity += neighbor->getVelocity();

  averageVelocity += boid->getVelocity();

  averageVelocity /= neighborhood.size() + 1;

  return Vector2f::normalized(averageVelocity);
}