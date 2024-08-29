#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

/// <summary>
/// Implemented
/// </summary>
Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  // done: add your code here to align each boid in a neighborhood
  Vector2f averageVelocity = Vector2f::zero();

  // Default to 0
  if (neighborhood.empty()) 
      return Vector2f::zero();


  for (Boid* neighbor : neighborhood)
    averageVelocity += neighbor->getVelocity();

  averageVelocity /= neighborhood.size();

  return Vector2f::normalized(averageVelocity);
}