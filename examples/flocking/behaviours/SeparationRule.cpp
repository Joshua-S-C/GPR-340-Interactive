#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

/// <summary>
/// Implemented. Clamps distance of boids and max force (max force via UI)
/// </summary>
Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    // Try to avoid boids too close
    Vector2f separatingForce = Vector2f::zero();

    float desiredDistance = desiredMinimalDistance;
    float desiredMaxSeparationForce = maxSeparationForce;

    // done: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them

    if (!neighborhood.empty()) {
        Vector2f position = boid->transform.position;
        int countCloseFlockmates = 0;
        // done: find and apply force only on the closest mates

        for (Boid* neighbor : neighborhood) {
            Vector2f neighborToBoid = (position - neighbor->getPosition());
            float n2bMagnitude = neighborToBoid.getMagnitude();

            if (n2bMagnitude > desiredDistance) continue;

            // Clamping distance so no dividing by 0
            if (n2bMagnitude == 0) {
                n2bMagnitude == .000001;
            }

            countCloseFlockmates++;

            separatingForce += neighborToBoid.normalized() / n2bMagnitude;
        }
    }

    // Clamping separation force
    if (separatingForce.getMagnitude() > desiredMaxSeparationForce) {
        separatingForce = Vector2f::normalized(separatingForce) * desiredMaxSeparationForce;
    }

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->window->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    if (ImGui::DragFloat("Max Separation Force", &maxSeparationForce, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
