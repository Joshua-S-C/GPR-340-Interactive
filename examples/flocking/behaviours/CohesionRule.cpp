#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  if (neighborhood.size() == 0)
    return cohesionForce;

  Vector2f centreOfMass = Vector2f::zero();

  // find center of mass
  for (Boid *neighbor : neighborhood)
    centreOfMass += neighbor->getPosition();

  centreOfMass /= neighborhood.size();

  cohesionForce = (centreOfMass - boid->getPosition()) / boid->getDetectionRadius();

  return cohesionForce;
}