/// <summary>
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Game {
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	// object init
	Player m_player;
	// Enemy m_enemy;
	Wanderer m_wander;
	Seeker m_seeker;
	ArriveSlower m_arriveSlower;
	ArriveFaster m_arriveFaster;
	Pursuer m_pursuer;
	// Fleer m_fleer;

	sf::Font m_instructionFont;
	sf::Text m_instructionText;
};

#endif // !GAME_HPP

