#include "Boid.h"
#include "Flock.h"

using namespace std;

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize()
{
	return flock.size();
}

Boid* Flock::getBoid(int i)
{
	return &flock[i];
}

void Flock::addBoid(Boid b)
{
	flock.push_back(b);
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking() 
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].run(flock);
	}
}
// Runs the swarm function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::swarming()
{
	for (int i = 0; i < flock.size(); i++)
	{
		flock[i].swarm(flock);
	}
}

void Flock::hForming(int t_leader)
{
    int fSize = flock.size();
    int hSpace = 20;  // Horizontal spacing between NPCs
    int vSpace = 20;  // Vertical spacing between NPCs
    int centralCount = 0;

    for (int i = 0; i < fSize; i++)
    {
        Pvector sum(0, 0);
        Pvector targetSlot(0, 0);
        Boid target = flock[t_leader]; // Our designated leader
        int closeEnough = 10;

        if (i == t_leader) {  // Deal with our leader here
            flock[i].update("hFormation");
            flock[i].borders();
        }
        else {
            // Calculate the position for each NPC in the 'H' formation
            if (i % 3 == 0) {
                // Central line
                targetSlot = target.location;
                targetSlot.x -= hSpace * (fSize / 3 / 2 - centralCount);
                targetSlot.y += (fSize / 3 / 2 + 1) * vSpace;
                centralCount++;
                if (centralCount == fSize / 3)
                {
                    centralCount = 0;
                }
            }
            else if (i % 3 == 1) {
                // Left line
                targetSlot = target.location;
                targetSlot.x -= hSpace * fSize / 3 / 2;
                targetSlot.y += (i / 3 + 1) * vSpace;
            }
            else {
                // Right line
                targetSlot = target.location;
                targetSlot.x += hSpace * fSize / 3 / 2;
                targetSlot.y += (i / 3 + 1) * vSpace;
            }

            Pvector sub = sub.subTwoVector(targetSlot, flock[i].location);
            float D = sub.magnitude();
            if (D > closeEnough) {
                sum = sub;
                sum.normalize();
                sum.mulScalar(flock[i].maxSpeed);
                flock[i].applyForce(sum);
                flock[i].update("hFormation");
                flock[i].borders();
            }
            else {
                flock[i].velocity = flock[t_leader].velocity;
                flock[i].borders();
            }
        }
    }
}