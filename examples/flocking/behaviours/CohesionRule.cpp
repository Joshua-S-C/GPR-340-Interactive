#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

/// <summary>
/// Implemeted
/// </summary>
Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // done: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

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