#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Behavior.h"

class Player {
public:
	Player() {
		setupSprite();

		// init pos
		m_kinematic.m_pos = sf::Vector2f(500.0f, 500.0f);
		m_playerSprite.setPosition(m_kinematic.m_pos);
	}

	void processKeys(sf::Event t_event) {
		if (sf::Keyboard::Up == t_event.key.code) {
			m_kinematic.m_velocity *= m_increment;
		}
		else if (sf::Keyboard::Down == t_event.key.code) {
			m_kinematic.m_velocity /= m_increment;
		}
	}

	void update(sf::Time t_deltaTime) {
		rotate(t_deltaTime);

		m_kinematic.m_velocity = m_forward * m_accelerator;
		m_kinematic.m_pos += m_kinematic.m_velocity * t_deltaTime.asSeconds();
		m_playerSprite.setPosition(m_kinematic.m_pos);
		
		// m_shape.setPosition(m_curPos);
	}

	void render(sf::RenderWindow& t_window) {
		t_window.draw(m_playerSprite);
		drawVelocityDirection(t_window, m_kinematic.m_pos, m_kinematic.m_velocity);
		checkBound(t_window);
		// t_window.draw(m_shape);
	}

	sf::Vector2f& getPos() { return m_kinematic.m_pos; }
	Kinematic& getKinematic() { return m_kinematic; }

private:

	void setupSprite() {
		// system("dir");

		m_playerTexture.loadFromFile("Blue.png");
		m_playerTexture.setSmooth(true);
		m_playerSprite.setTexture(m_playerTexture);
		m_playerSprite.setOrigin(sf::Vector2f(m_playerSprite.getGlobalBounds().width / 2.0f,
			m_playerSprite.getGlobalBounds().height / 2.0f));
	}

	void checkBound(sf::RenderWindow& t_window) {
		sf::FloatRect bounds = m_playerSprite.getGlobalBounds();
		float windowWidth = static_cast<float>(t_window.getSize().x);
		float windowHeight = static_cast<float>(t_window.getSize().y);

		// Wrap horizontally
		if (m_kinematic.m_pos.x + bounds.width < 0) {
			m_kinematic.m_pos.x = windowWidth;
		}
		else if (m_kinematic.m_pos.x > windowWidth) {
			m_kinematic.m_pos.x = -bounds.width;
		}

		// Wrap vertically
		if (m_kinematic.m_pos.y + bounds.height < 0) {
			m_kinematic.m_pos.y = windowHeight;
		}
		else if (m_kinematic.m_pos.y > windowHeight) {
			m_kinematic.m_pos.y = -bounds.height;
		}
	}

	void rotate(sf::Time& t_deltaTime) {
		float rotation = m_playerSprite.getRotation() * 3.14159f / 180.0f;
		float deltaTime = t_deltaTime.asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			m_playerSprite.rotate(-m_rotateVelocity * deltaTime);
			m_forward = sf::Vector2f(std::sin(rotation), -std::cos(rotation));

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			m_playerSprite.rotate(m_rotateVelocity * deltaTime);
			m_forward = sf::Vector2f(std::sin(rotation), -std::cos(rotation));
		}
	}

	void drawVelocityDirection(sf::RenderWindow& t_window, const sf::Vector2f& t_pos, const sf::Vector2f& t_velocity) {
		if (t_velocity.x == 0.0f && t_velocity.y == 0.0f)  {
			return;
		}

		sf::VertexArray line(sf::Lines, 2);

		line[0].position = t_pos;
		line[0].color = sf::Color::Green;
		sf::Vector2f normalizedVelocity = t_velocity / std::sqrt(t_velocity.x * t_velocity.x + t_velocity.y * t_velocity.y);
		line[1].position = t_pos + normalizedVelocity * 200.0f;
		line[1].color = sf::Color::Green;

		t_window.draw(line);
	}


	sf::CircleShape m_shape;
	sf::Texture m_playerTexture; // texture used for sfml logo
	sf::Sprite m_playerSprite; // sprite used for sfml logo
	// sf::Vector2f m_curPos; // current position of player

	// sf::Vector2f m_velocity;
	float m_accelerator = 300.0f;
	float m_rotateVelocity = 180.0f;
	sf::Vector2f m_forward;
	// float m_curRotation;

	float m_increment = 1.03f;

	Kinematic m_kinematic;
};

#endif // !PLAYER_HPP

