#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2f force = Vector2f::zero();
    Vector2f position = boid->getPosition();

    // Return a force proportional to the proximity of the boids with the bounds, and opposed to it
    // This is how it's supposed to be implemented according to the comment
    if (!useDistanceFromBorder)
    {
        // Horizontal
        if (position.x > this->world->engine->window->size().x - desiredDistance)
            force.x -= (position.x - (this->world->engine->window->size().x - desiredDistance));

        if (position.x < 0 + desiredDistance)
            force.x -= (position.x - (0 + desiredDistance));

        // Vertical
        if (position.y > this->world->engine->window->size().y - desiredDistance)
            force.y -= (position.y - (this->world->engine->window->size().y - desiredDistance));

        if (position.y < 0 + desiredDistance)
            force.y -= (position.y - (0 + desiredDistance));

        return force;
    }

    // A different way to do something similar. Although it doesn't work well lol
    // Basically a harder barrier by directly changing velocity
    Vector2f newVel = boid->getVelocity();

    // Horizontal
    if (position.x > this->world->engine->window->size().x - desiredDistance)
        newVel.x = (-abs(boid->getVelocity().x));

    if (position.x < 0 + desiredDistance) 
        newVel.x = (abs(boid->getVelocity().x));

    // Vertical
    if (position.y > this->world->engine->window->size().y - desiredDistance) 
        newVel.y = (-abs(boid->getVelocity().y));

    if (position.y < 0 + desiredDistance) 
        newVel.y = (abs(boid->getVelocity().y));

    boid->setVelocity(newVel);

    return force;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

    // Added - Not working yet cuz it keeps resetting itself
    if (ImGui::RadioButton("Use Distance from Border", useDistanceFromBorder)) {
        useDistanceFromBorder = true;
        valueHasChanged = true;
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Directly Change Velocity", !useDistanceFromBorder)) {
        useDistanceFromBorder = false;
        valueHasChanged = true;
    }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Gray);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Gray);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Gray);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Gray);                    // LEFT
}