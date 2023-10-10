Step 4: Can you improve the code so that the flocking runs more fluidly at higher numbers of boids?

I setup a clock check for force calculation inside the FLOCK function
And Enable rand position spawn for boids instead of spawning every boid on one position

if (m_clock.getElapsedTime().asSeconds() > 0.02) // Update every 0.02 seconds
{
	sep = Separation(v);
	ali = Alignment(v);
	coh = Cohesion(v);
}