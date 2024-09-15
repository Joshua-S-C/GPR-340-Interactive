//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
    Point2D point = {0, 0};

    for (int row = 0; row < world.SideSize(); row++, point.y = row) {
        for (int col = 0; col < world.SideSize(); col++) {
            point.x = col;

            int neighbors = CountNeighbors(world, point);
            bool alive = world.Get(point);

            //Dead Cell
            if (!alive) {
                if (neighbors == 2)
                    world.SetNext(point, true);
                else
                    world.SetNext(point, false);
            } else {
                // Live Cell
                if (neighbors == 2)
                    world.SetNext(point, true);
                else
                    world.SetNext(point, false);
            }

        }
    }

    world.SwapBuffers();
}


int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) { 
	int neighbors = 0;

    if (point.x % 2 == 0) {
        // Up Left
        neighbors += world.Get(point + point.UP + point.LEFT);

        // Up Right
        neighbors += world.Get(point + point.UP);

        // Down Left
        neighbors += world.Get(point + point.DOWN + point.LEFT);

        // Down Right
        neighbors += world.Get(point + point.DOWN);
    }

    if (point.x % 2 == 1) {
	    // Up Left
	    neighbors += world.Get(point + point.UP);

	    // Up Right
	    neighbors += world.Get(point + point.UP + point.RIGHT);

	    // Down Left
	    neighbors += world.Get(point + point.DOWN);

	    // Down Right
        neighbors += world.Get(point + point.DOWN + point.RIGHT);
    }

    // Right
    neighbors += world.Get(point + point.RIGHT);

    // Left
    neighbors += world.Get(point + point.LEFT);

	return neighbors;
}
