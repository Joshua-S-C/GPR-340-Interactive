#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

/// <summary>
/// Implemeted
/// </summary>
Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  if (neighborhood.empty())
    return cohesionForce;

  Vector2f centreOfMass = Vector2f::zero();

  // find center of mass
  for (Boid* neighbor : neighborhood)
    centreOfMass += neighbor->getPosition();

  centreOfMass /= neighborhood.size();

  cohesionForce = (centreOfMass - boid->getPosition()) / boid->getDetectionRadius();

  return cohesionForce;
}