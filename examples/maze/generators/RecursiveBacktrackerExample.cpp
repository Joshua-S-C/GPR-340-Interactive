#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

    Point2D p;

    // Default
    if (stack.empty()) {
        //p = randomStartPoint(w);
        p = {0, 0};
        stack.push_back(p);
    } else {
        p = stack.back();
    }

    // Check neighbors to visit
    std::vector<Point2D> visitables = getVisitables(w, p);

    // Check valid neighbor not in stack
    if (!stack.empty() &&
        !visitables.empty()
        // Check that it's not off the world border
        ) {

        // Randomly select neighbor
        int rando = randNums[randNumIndex];
        randNumIndex++;
        rando %= visitables.size();
        Point2D neighbor = visitables[rando];

        // Add to stack
        stack.push_back(neighbor);

        // Break wall between current and chosen neighbor // Using the SetNorth/South/Etc
        Node neighborNode = w->GetNode(neighbor);

        // Find out which direction it is!!!
        w->SetNode(neighbor, );


        return true;
    } else {
        stack.pop_back();
    
        return false;
    }

}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this

  // World only stores walls. 
  // GetNorth/South/etc gets the walls
  // If you want to check if it is visited, get the color
  // Up, Right, Down, Left
  /*Gray*/

  if (w->GetNodeColor(p + p.UP) == Color::DarkGray) 
      visitables.push_back(p + p.UP);

  if (w->GetNodeColor(p + p.RIGHT) == Color::DarkGray) 
      visitables.push_back(p.RIGHT);

  if (w->GetNodeColor(p + p.DOWN) == Color::DarkGray) 
      visitables.push_back(p.DOWN);

  if (w->GetNodeColor(p + p.LEFT) == Color::DarkGray) 
      visitables.push_back(p.LEFT);

  return visitables;
}
