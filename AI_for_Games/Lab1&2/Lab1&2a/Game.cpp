#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1920U, 1080U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game() {

}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run() {	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen()) {
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents() {
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent)) {
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event) {
	if (sf::Keyboard::Escape == t_event.key.code) {
		m_exitGame = true;
	}
	if (t_event.key.code == sf::Keyboard::Num1) {
		m_wander.isActive() ? m_wander.setActive(false) : m_wander.setActive(true);
		std::cout << "Num1 press detected \n";
	}
	if (t_event.key.code == sf::Keyboard::Num2) {
		m_seeker.isActive() ? m_seeker.setActive(false) : m_seeker.setActive(true);
	}
	if (t_event.key.code == sf::Keyboard::Num3) {
		m_arriveSlower.isActive() ? m_arriveSlower.setActive(false) : m_arriveSlower.setActive(true);
	}
	if (t_event.key.code == sf::Keyboard::Num4) {
		m_arriveFaster.isActive() ? m_arriveFaster.setActive(false) : m_arriveFaster.setActive(true);
	}
	if (t_event.key.code == sf::Keyboard::Num5) {
		m_pursuer.isActive() ? m_pursuer.setActive(false) : m_pursuer.setActive(true);
	}
	m_player.processKeys(t_event);
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime) {
	if (m_exitGame) {
		m_window.close();
	}

	m_player.update(t_deltaTime);

	m_wander.update(t_deltaTime, m_player.getPos(), m_player.getKinematic());
	m_seeker.update(t_deltaTime, m_player.getPos(), m_player.getKinematic());
	m_arriveSlower.update(t_deltaTime, m_player.getPos(), m_player.getKinematic());
	m_arriveFaster.update(t_deltaTime, m_player.getPos(), m_player.getKinematic());
	m_pursuer.update(t_deltaTime, m_player.getPos(), m_player.getKinematic());
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render() {
	m_window.clear(sf::Color::Black);

	m_player.render(m_window);

	m_wander.render(m_window, m_player.getPos());
	m_arriveSlower.render(m_window, m_player.getPos());
	m_arriveFaster.render(m_window, m_player.getPos());
	m_seeker.render(m_window, m_player.getPos());
	m_pursuer.render(m_window, m_player.getPos());

	m_window.draw(m_instructionText);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText() {
	m_instructionFont.loadFromFile("Freedom-10eM.ttf");
	m_instructionText.setFont(m_instructionFont);
	m_instructionText.setCharacterSize(32);
	m_instructionText.setString("Press Num one to five to either Pause or continue the enemies' movements");
	m_instructionText.setFillColor(sf::Color::White);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite() {

}
