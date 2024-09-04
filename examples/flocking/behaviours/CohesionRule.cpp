#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

/// <summary>
/// Implemented
/// </summary>
Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Default to 0
  if (neighborhood.empty())
    return Vector2f::zero();

  Vector2f cohesionForce = Vector2f::zero();
  Vector2f centreOfMass = Vector2f::zero();

  // Centre of mass
  for (Boid* neighbor : neighborhood)
    centreOfMass += neighbor->getPosition();
  centreOfMass /= neighborhood.size();

  cohesionForce = (centreOfMass - boid->getPosition()) / boid->getDetectionRadius();

  return cohesionForce;
}