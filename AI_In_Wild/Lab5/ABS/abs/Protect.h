#ifndef PROTECT_H
#define PROTECT_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>

class Protect : public Routine
{

public:

    int destX;
    int destY;
    sf::Vector2f target;
    int droidA;
    int droidB;

    Protect(int droidA, int droidB, Grid& g) : Routine()    // Superclass constructor
    {
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "Protect";
        this->routineGrid = &g;

        // If we get -1 passed in then we will self select the droids in 'Act' below, so leave it as -1.
        // Otherwise subtract 1 so we map to the correct index which starts at 0
        this->droidA = droidA;
        this->droidB = droidB;
        if (droidA != -1) this->droidA = droidA - 1;
        if (droidB != -1) this->droidB = droidB - 1;

    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        if (isRunning())
        {
            if (!droid->isAlive() || droid->alarmHasBeenRaised)
            {
                fail();
                return;
            }

            sf::Vector2f protectPoint = getProtectPoint(grid);
            destX = round(protectPoint.x);
            destY = round(protectPoint.y);

            if (destX < 1) destX = 1;
            if (destY < 1) destY = 1;
            if (destX > grid.gridSize) destX = grid.gridSize;
            if (destY > grid.gridSize) destY = grid.gridSize;

            droid->target = grid.getGridLocation(destX, destY);
            if (!isDroidAtDestination(droid, grid)) {
                moveDroid(droid, grid);
            }
            else {
                succeed("Protect for " + droid->name);
            }
        }
    }

    sf::Vector2f getProtectPoint(Grid& grid)
    {
        sf::Vector2f protectPoint;

        float droidAx = grid.m_gridDroids[droidA]->x;
        float droidAy = grid.m_gridDroids[droidA]->y;
        float droidBx = grid.m_gridDroids[droidB]->x;
        float droidBy = grid.m_gridDroids[droidB]->y;

        protectPoint.x = (droidAx + droidBx) / 2.0f;
        protectPoint.y = (droidAy + droidBy) / 2.0f;

        float currentPointDistanceToA = std::sqrtf(std::pow(droidAx - destX, 2) + std::pow(droidAy - destY, 2));
        float currentPointDistanceToB = std::sqrtf(std::pow(droidBx - destX, 2) + std::pow(droidBy - destY, 2));

        // Determine the direction to move based on the relative position of droids A and B
        int deltaX = (droidAx < droidBx) ? 1 : -1;
        int deltaY = (droidAy < droidBy) ? 1 : -1;

        if (currentPointDistanceToA < currentPointDistanceToB) {
            // Closer to A, move towards A
            protectPoint.x = (droidAx != droidBx) ? droidAx + deltaX : droidAx;
            protectPoint.y = (droidAy != droidBy) ? droidAy + deltaY : droidAy;
        }
        else {
            // Closer to B or equidistant, move towards B
            protectPoint.x = (droidAx != droidBx) ? droidBx - deltaX : droidBx;
            protectPoint.y = (droidAy != droidBy) ? droidBy - deltaY : droidBy;
        }

        // Adjust for cases where droids are aligned either horizontally or vertically
        if (droidAx == droidBx) {
            protectPoint.x = droidAx;
        }
        if (droidAy == droidBy) {
            protectPoint.y = droidAy;
        }

        return protectPoint;
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
        std::cout << ">>> Droid " << droid->name << " moving to " << destX << ", " << destY << std::endl;

        if (destX < 1 || destX > grid.gridSize || destY < 1 || destY > grid.gridSize)
            return;

        sf::Vector2f direction = droid->target - droid->position;
        if (std::abs(grid.length(direction)) > 0)
        {
            if (droid->target.y != droid->position.y)
            {
                if (droid->target.y > droid->position.y)
                {
                    droid->position.y = droid->position.y + 1;
                }
                else {
                    droid->position.y = droid->position.y - 1;
                }
            }
            if (droid->target.x != droid->position.x)
            {
                if (droid->target.x > droid->position.x)
                {
                    droid->position.x = droid->position.x + 1;
                }
                else {
                    droid->position.x = droid->position.x - 1;
                }
            }
        }

        if (isDroidAtDestination(droid, grid)) {
            succeed("MoveTo for " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
        return ((int)grid.length(direction) == 0);
    }
};
#endif