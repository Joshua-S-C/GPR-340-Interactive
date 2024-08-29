#ifndef SEPARATIONRULE_H
#define SEPARATIONRULE_H

#include "FlockingRule.h"

/* Steer to avoid local flockmates */
class SeparationRule : public FlockingRule {
private:
  float desiredMinimalDistance = 10;
  float maxSeparationForce = 100;    /// Clamp for separation force. There's also another catch for this to clamp the actual distance before division, so this was actually never hit

public:
  explicit SeparationRule(World* pWorld, float desiredSeparation = 20., float weight = 1., bool isEnabled = true)
      : FlockingRule(pWorld, Color::Red, weight, isEnabled), desiredMinimalDistance(desiredSeparation) {}

  std::unique_ptr<FlockingRule> clone() override { return std::make_unique<SeparationRule>(*this); }

  const char* getRuleName() override { return "Separation Rule"; }

  const char* getRuleExplanation() override { return "Steer to avoid collision with nearby boids."; }

  virtual float getBaseWeightMultiplier() override { return 1.f; }

  Vector2f computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) override;

  bool drawImguiRuleExtra() override;
};

#endif
