#include "JohnConway.h"

// Reference: https://playgameoflife.com/info

/// <summary>
/// Implemented
/// </summary>
void JohnConway::Step(World& world) {
	Point2D point = {0, 0};

    for (int row = 0; row < world.SideSize(); row++, point.y = row) {
        for (int col = 0; col < world.SideSize(); col++) {
            point.x = col;

            int neighbors = CountNeighbors(world, point);
            bool alive = world.Get(point);

            // Dead Cell
            if (!alive)
            {
                if (neighbors == 3)
                    world.SetNext(point,true);
                else
                    world.SetNext(point, false);
            } else {
                // Live Cell
                if (neighbors < 2 || neighbors > 3) 
                    world.SetNext(point, false);
                else
                    world.SetNext(point, true);
            }
        }
    }
  

  world.SwapBuffers();
}

/// <summary>
/// Implemented
/// </summary>
int JohnConway::CountNeighbors(World& world, Point2D point) {
  int neighbors = 0;
   
  // Cardinal Neighbord
  neighbors += world.Get(point + point.UP);
  neighbors += world.Get(point + point.RIGHT);
  neighbors += world.Get(point + point.DOWN);
  neighbors += world.Get(point + point.LEFT);

  // Diagonal Neighbors
  neighbors += world.Get(point + point.UP + point.RIGHT);
  neighbors += world.Get(point + point.RIGHT + point.DOWN);
  neighbors += world.Get(point + point.DOWN + point.LEFT);
  neighbors += world.Get(point + point.LEFT + point.UP);

  return neighbors;
}
