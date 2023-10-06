Step 4: Can you improve the code so that the flocking runs more fluidly at higher numbers of boids?

I setup a clock check for force calculation inside the FLOCK function


if (m_clock.getElapsedTime().asSeconds() > 2.0) // Update every 2 seconds
{
	sep = Separation(v);
	ali = Alignment(v);
	coh = Cohesion(v);
}