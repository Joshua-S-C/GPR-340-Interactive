#include "Catcher.h"
#include "World.h"


Point2D Catcher::Move(World* world) {
	std::vector<Point2D> path = generatePath(world);

	if (path.empty()) return MoveRandom(world);

	return path.front();
}

Point2D Catcher::MoveRandom(World* world) { 
	auto side = world->getWorldSideSize() / 2;
	for (;;) {
	  Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};

	  if (isValidPoint(world, p)) 
		  return p;
	}
}