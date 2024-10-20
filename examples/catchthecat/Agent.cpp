#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

using namespace std;

// From Tolstenko
struct AStarNode {
  Point2D point;
  int accDist;
  int heuristicDist;

  /// <summary>
  /// Overloaded to use with priority queue
  /// Takes into account bpth Euclidean Distnace & Heuristic Distance
  /// </summary>
  bool operator<(const AStarNode& rhs) const { return accDist + heuristicDist > rhs.accDist + rhs.heuristicDist; }
};

#define DEBUG

std::vector<Point2D> Agent::generatePath(World* w) {
    unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
    priority_queue<AStarNode> frontier;          // to store next ones to visit.
    unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
    unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

    // Bootstrap state
    Point2D catPos = w->getCat();
    frontier.push({catPos, 0, 0});
    frontierSet.insert(catPos);
    Point2D borderExit = Point2D::INFINITE;   // if at the end of the loop we dont find a border, we have to return random points

    #ifdef DEBUG
    int nodesSearched = 1;
    #endif  // DEBUG

    while (!frontier.empty() && borderExit == Point2D::INFINITE) {
        // Get the current from frontier
        AStarNode current = frontier.top();
        frontier.pop();

        // Mark current as visited
        visited[current.point] = true;

        // Iterate over the neighs: for every neighbor set the cameFrom
        std::vector<Point2D> visitables = getVisitableNeightbors(w, current.point, frontierSet);

        for (Point2D neighbor : visitables) {
            #ifdef DEBUG
            nodesSearched++;
            #endif  // DEBUG

            cameFrom[neighbor] = current.point;
        
            // Enqueue the neighbors to frontier and frontierset
            frontier.push({
                neighbor, 
                current.accDist + 1, 
                getHeuristic(neighbor, w->getWorldSideSize())
            });

            frontierSet.insert(neighbor);

            // Break when found a visitable border
            if (isPointBorder(w, neighbor)) borderExit = neighbor;
        }
    }

    
    #ifdef DEBUG
    cout << nodesSearched << endl;
    #endif  // DEBUG

    // If there isnt a reachable border, just return empty vector
    if (borderExit == Point2D::INFINITE)
        return vector<Point2D>();

    // If the border is not infinity, build the path from border to the cat using the camefrom map
    std::vector<Point2D> path;
    Point2D current = borderExit;

    do {
        path.push_back(current);
        current = cameFrom[current];
    } while (current != catPos);

    // If your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
    return path;
}

#pragma region Helpers

/// <summary>
/// Use to set the Heuristic Distance in A* Node
/// From Tolstenko
/// </summary>
/// <param name="p">The point of the node being set</param>
/// <param name="sideSize">w-getSideSize()</param>
/// <returns>A*Node.heuristicDist</returns>
int Agent::getHeuristic(Point2D p, int sideSize) {
    // Right Side
    if (p.x - p.y > 0 && p.x + p.y > 0)
        return (sideSize / 2) - p.x;

    // Left Side
    if (p.x - p.y < 0 && p.x + p.y < 0)
        return (sideSize / 2) + p.x;

    // Down
    if (p.y - p.x > 0 && p.y + p.x > 0) 
        return (sideSize / 2) - p.y;

    // Up
    if (p.y - p.x < 0 && p.y + p.x < 0) 
        return (sideSize / 2) + p.y;
}

/// <returns>True if point is on the border</returns>
bool Agent::isPointBorder(World* w, Point2D p) { 
    return (
        abs(p.x) == w->getWorldSideSize() / 2 || 
        abs(p.y) == w->getWorldSideSize() / 2); 
}

/// <returns>True if the point is not a wall or the cat</returns>
bool Agent::isValidPoint(World* w, Point2D p) {
    return !w->getContent(p) && w->getCat() != p;
}

/// <summary>
/// Valid neighbors: not visited, not the cat, not the block, not in the queue
/// </summary>
/// <returns>Vector of valid neighbors</returns>
std::vector<Point2D> Agent::getVisitableNeightbors(World* w, Point2D p, unordered_set<Point2D> frontierSet) { 
    std::vector<Point2D> visitables;
    Point2D directions[6] = {World::NE(p), World::NW(p), World::E(p), World::W(p), World::SE(p), World::SW(p)};

    for (Point2D neighbor : directions) {
        if (frontierSet.contains(neighbor) || !isValidPoint(w, neighbor)) 
            continue;

        visitables.push_back(neighbor);
    }
    
    return visitables; 
}

#pragma endregion
