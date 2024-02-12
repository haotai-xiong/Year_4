#ifndef ARRIVE_H
#define ARRIVE_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

class Arrive : public Routine
{

public:

    int destX;
    int destY;
    sf::Vector2f target;
    int droidA;
    float arriveSpeed = 1.0f;
    float arriveDistance = 290.0f;
    bool arriving = false;
    // int droidB;

    Arrive(int droidA, /*int droidB,*/ Grid& g) : Routine()    // Superclass constructor
    {
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "Arrive";
        this->routineGrid = &g;

        // If we get -1 passed in then we will self select the droids in 'Act' below, so leave it as -1.
        // Otherwise subtract 1 so we map to the correct index which starts at 0
        this->droidA = droidA;
        // this->droidB = droidB;
        if (droidA != -1) this->droidA = droidA - 1;
        // if (droidB != -1) this->droidB = droidB - 1;

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

            /*
            sf::Vector2f approachPoint = approaching(droid, grid);
            destX = round(approachPoint.x);
            destY = round(approachPoint.y);
            */

            destX = grid.m_gridDroids[droidA]->x;
            destY = grid.m_gridDroids[droidA]->y;

            arrived(droid);

            if (destX < 1) destX = 1;
            if (destY < 1) destY = 1;
            if (destX > grid.gridSize) destX = grid.gridSize;
            if (destY > grid.gridSize) destY = grid.gridSize;

            droid->target = grid.getGridLocation(destX, destY);
            if (!isDroidAtDestination(droid, grid)) {
                moveDroid(droid, grid);
            }
            else {
                succeed("Arriving for " + droid->name);
            }
        }
    }

    void arrived(Droid* droid)
    {
        float distanceBetween = std::sqrtf(std::powf(droid->position.x - destX, 2) + std::powf(droid->position.y - destY, 2)); 

        float speedReductionFactor = std::max(0.0f, std::min(1.0f, distanceBetween / arriveDistance));
        float minSpeed = 0.05f;
        float newSpeed = minSpeed + speedReductionFactor * (arriveSpeed - minSpeed);

        if (distanceBetween < arriveDistance) {
            arriveSpeed = newSpeed;
        }
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
                    droid->position.y = droid->position.y + arriveSpeed;
                }
                else {
                    droid->position.y = droid->position.y - arriveSpeed;
                }
            }
            if (droid->target.x != droid->position.x)
            {
                if (droid->target.x > droid->position.x)
                {
                    droid->position.x = droid->position.x + arriveSpeed;
                }
                else {
                    droid->position.x = droid->position.x - arriveSpeed;
                }
            }
        }

        if (isDroidAtDestination(droid, grid)) {
            succeed("Arriving to " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
        return ((int)grid.length(direction) == 0);
    }
};
#endif