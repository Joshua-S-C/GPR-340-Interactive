#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
    std::vector<Point2D> path = generatePath(world);
    
    if (path.empty()) return MoveRandom(world);

    return path.front();
}

Point2D Cat::MoveRandom(World* world) { 
    auto p = world->getCat();
    Point2D move;
  
    // Get Valid Moves
    std::vector<Point2D> visitables;
    Point2D directions[6] = {World::NE(p), World::NW(p), World::E(p), World::W(p), World::SE(p), World::SW(p)};

    for (Point2D option : directions)
        if (isValidPoint(world, p)) visitables.push_back(option);

    if (visitables.empty()) return directions[0];

    auto rand = Random::Range(0, visitables.size()-1);

    return visitables[rand];
}

