#ifndef MAZEGENERATORBASE_H
#define MAZEGENERATORBASE_H

#include <string>
#include "math/Point2D.h"
#include "generators//PRNG.h"

class World;

class MazeGeneratorBase {
public:
    MazeGeneratorBase() = default;
    virtual std::string GetName() = 0;
    // Step should return true if it made changes in the world
    virtual bool Step(World* world) = 0;
    // Clears and resets all data from the generator
    virtual void Clear(World* world) = 0;
    virtual ~MazeGeneratorBase() = default;

#pragma region Added Functions and Vars

    bool centerStartPoint = false;

    // True = use Xorshift, False = use the numbers you gave us on the website
    bool useRandom = false;

    Xorshift prng;
    int randNumIndex = 0;
    int randNums[100]
        = {72, 99, 56, 34, 43, 62, 31, 4,  70, 22, 6,  65, 96, 71, 29, 9,  98, 41, 90, 7,  30, 3,  97, 49, 63, 88, 47, 82, 91, 54, 74, 2,  86, 14,
            58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5,  24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1,  0,
            38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8,  32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

    /// <summary>
    /// Added
    /// </summary>
    /// <param name="p">Point to be evaluated</param>
    /// <param name="worldSizeOver2">w->worldSize()/2</param>
    /// <returns>True if the point fits in the World bounds based on size</returns>
    bool pointInWorld(Point2D p, int worldSizeOver2) {
        if (p.x > worldSizeOver2) return false;
        if (p.x < -worldSizeOver2) return false;

        if (p.y > worldSizeOver2) return false;
        if (p.y < -worldSizeOver2) return false;

        return true;
    }

    /// <summary>
    /// Generates a random number and does the stuff needed to deal with that
    /// </summary>
    /// <returns>The next random number</returns>
    int getRandomIndex() {
        int rando;

        if (useRandom) {
            prng.shift();
            rando = prng.a;
        } else {
            if (randNumIndex > 99) randNumIndex = 0;

            rando = randNums[randNumIndex];
            randNumIndex++;
        }

        return rando;
    }

#pragma endregion

};

#endif  // MAZEGENERATORBASE_H
