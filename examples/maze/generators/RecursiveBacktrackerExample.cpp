#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

/// <summary>
/// Implemented
/// </summary>
bool RecursiveBacktrackerExample::Step(World* w) {
    Point2D p;

    // Starting
    if (stack.empty()) {
        //p = randomStartPoint(w);
        p = {0, 0};

        // The End
        if (w->GetNodeColor(p) == Color::Black) return false;

        stack.push_back(p);
    } else {
        p = stack.back();
    }

    // Check neighbors to visit
    std::vector<Point2D> visitables = getVisitables(w, p);

    if (!visitables.empty()) {
        // Mark as visited
        w->SetNodeColor(p, Color::Red); 

        // Select neighbor
        Point2D neighbor;
        if (visitables.size() > 1)
          neighbor = visitables[getRandomIndex() % visitables.size()];
        else
          neighbor = visitables[0];

        // Add to stack
        stack.push_back(neighbor);
         
        // Break wall between current and chosen neighbor Using the SetNorth/South/Etc
        Node nNode = w->GetNode(neighbor);

        // Find out which direction it is
        Point2D dir = neighbor - p;
        Node pNode = w->GetNode(p);

        // There HAS to be a better way :(
        if (dir == Point2D::UP) {
            pNode.SetNorth(false);
            nNode.SetSouth(false);
        } else if (dir == Point2D::DOWN) {
            pNode.SetSouth(false);
            nNode.SetNorth(false);
        } else if (dir == Point2D::LEFT) {
            pNode.SetWest(false);
            nNode.SetEast(false);
        } else if (dir == Point2D::RIGHT) {
            pNode.SetEast(false);
            nNode.SetWest(false);
        }

        // Set walls
        w->SetNode(neighbor, nNode);
        w->SetNode(p, pNode);

         return true;
    }

    // If no neighbors: Remove top cell from the stack, backtracking
    stack.pop_back();
    w->SetNodeColor(p, Color::Black);
    return true;
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

/// <summary>
/// Implemented
/// </summary>
/// <returns>Vector of valid points. Points that are off the World are not valid</returns>
std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
    // World only stores walls. GetNorth/South/etc gets the walls
    // If you want to check if it is visited, get the color
    // Order: Up, Right, Down, Left
  
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;

    /*Gray = Not Visisted*/

    if (pointInWorld(p + p.UP, sideOver2) && w->GetNodeColor(p + p.UP) == Color::DarkGray)
        visitables.push_back(p + p.UP);

    if (pointInWorld(p + p.RIGHT, sideOver2) && w->GetNodeColor(p + p.RIGHT) == Color::DarkGray) 
        visitables.push_back(p + p.RIGHT);

    if (pointInWorld(p + p.DOWN, sideOver2) && w->GetNodeColor(p + p.DOWN) == Color::DarkGray) 
        visitables.push_back(p + p.DOWN);

    if (pointInWorld(p + p.LEFT, sideOver2) && w->GetNodeColor(p + p.LEFT) == Color::DarkGray) 
        visitables.push_back(p + p.LEFT);

    return visitables;
}

/// <summary>
/// Added
/// </summary>
/// <param name="p">Point to be evaluated</param>
/// <param name="worldSizeOver2">w->worldSize()/2</param>
/// <returns>True if the point fits in the World bounds based on size</returns>
bool RecursiveBacktrackerExample::pointInWorld(Point2D p, int worldSizeOver2) {
    if (p.x > worldSizeOver2) return false;
    if (p.x < -worldSizeOver2) return false;

    if (p.y > worldSizeOver2) return false;
    if (p.y < -worldSizeOver2) return false;

    return true;
}