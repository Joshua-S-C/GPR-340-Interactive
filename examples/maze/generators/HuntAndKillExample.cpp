#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>

/// <summary>
/// Implemented
/// </summary>
bool HuntAndKillExample::Step(World* w) {
    Point2D p;

    // Starting
    if (stack.empty()) {
        if (randStartPoint)
            p = randomStartPoint(w);
        else
            p = {0, 0};

        // The End
        if (w->GetNodeColor(p) == Color::Black) return false;

        stack.push_back(p);
        } else {
        p = stack.back();
    }

    // Check neighbors to visit
    std::vector<Point2D> visitables = getVisitables(w, p);

    // Mark as visited
    w->SetNodeColor(p, Color::Black);

    // Visit neighbors, Same as DFS
    if (!visitables.empty()) {
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

    // No neighbors: Walk / Scan for first unvisited cell with a visisted neighbor
    std::vector<Point2D> neighbors;

    for (int i = -(w->GetSize() / 2); i <= w->GetSize() / 2; i++)
    for (int j = -(w->GetSize() / 2); j <= w->GetSize() / 2; j++) {
        p.x = j;
        p.y = i;

        if (w->GetNodeColor(p) == Color::DarkGray) {
            neighbors = getVisitedNeighbors(w, p);

            // Break walls and add Point to stack to start from there next
            if (!neighbors.empty()) {
                Point2D dir;

                if (visitables.size() > 1)
                    dir = neighbors[getRandomIndex() % neighbors.size()];
                else
                    dir = neighbors.front();

                Node pNode = w->GetNode(p);
                Node nNode = w->GetNode(p + dir);

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

                w->SetNode(p+ dir, nNode);
                w->SetNode(p, pNode);

                w->SetNodeColor(p, Color::Black);
            
                stack.push_back(p);
            
                return true;
            }
        }
    }

  // The End also
  return false;
}

void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D HuntAndKillExample::randomStartPoint(World* world) {
    auto sideOver2 = world->GetSize() / 2;
    return {getRandomIndex() % sideOver2, getRandomIndex() % sideOver2};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;

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
/// Used when walking to get the neighbor to break the wall
/// </summary>
/// <returns>The deltas that lead to visited neighbors</returns>
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
    std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> neighbors;

    for (int i = 0; i < 3; i++) {
        Point2D thePoint = p + deltas[i];
        if (pointInWorld(p + deltas[i], sideOver2) && w->GetNodeColor(p + deltas[i]) == Color::Black) 
            neighbors.push_back(deltas[i]);
    }

    return neighbors;
}
