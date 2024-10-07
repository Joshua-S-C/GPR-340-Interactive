#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

using namespace std;

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2D> frontier;          // to store next ones to visit.
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // Bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  
  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // Get the current from frontier
    Point2D current = frontier.top();
    frontier.pop();

    // Remove the current from frontierset
    frontierSet.find(current);

    // Mark current as visited
    visited[current] = true;

    std::vector<Point2D> visitables = getVisitableNeightbors(w, current, &frontierSet);

    // Iterate over the neighs: for every neighbor set the cameFrom
    for (Point2D neighbor : visitables) {

        cameFrom[neighbor] = current;
        
        // Enqueue the neighbors to frontier and frontierset
        frontier.push(neighbor);
        frontierSet.insert(neighbor);

        // Break when found a visitable border
        if (isPointBorder(w, neighbor)) {
            break;
        }
    }

  }

  // If there isnt a reachable border, just return empty vector
  if (!isPointBorder(w, frontierSet.begin())) // Make this correct tho
    return vector<Point2D>();

  // If the border is not infinity, build the path from border to the cat using the camefrom map



  // If your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
}

/// <returns>True if point is on the border</returns>
bool Agent::isPointBorder(World* w, Point2D p) { return (p.x == w->getWorldSideSize() / 2 && p.y == w->getWorldSideSize() / 2); }

/// <returns>True if the point is not a wall or the cat</returns>
bool Agent::isValidPoint(World* w, Point2D p) {
  Point2D catPos = w->getCat();

  return !w->getContent(p) && catPos != p;
}

/// <summary>
/// Valid neighbors: not visited, not the cat, not the block, not in the queue
/// </summary>
/// <returns>Vector of valid neighbors</returns>
std::vector<Point2D> Agent::getVisitableNeightbors(World* w, Point2D p, const unordered_set<Point2D>* frontierSet) { 
    std::vector<Point2D> visitables;
    Point2D directions[6] = {World::NE(p), World::NW(p), World::E(p), World::W(p), World::SE(p), World::SW(p)};

    for (Point2D neighbor : directions) {
        if (frontierSet->contains(neighbor) || !isValidPoint(w, p)) 
            continue;

        visitables.push_back(neighbor);
    }
    
    return visitables; 
}



// Add Manhattan distance function for heuristics