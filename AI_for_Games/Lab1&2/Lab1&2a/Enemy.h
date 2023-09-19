#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

struct Kinematic {
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	float m_orientation;
	float m_rotation;
};

class Enemy
{
public:
	Enemy() {
		init();
	}

	virtual void update(sf::Time t_deltaTime) {
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

	virtual void render(sf::RenderWindow& t_window)	{
		m_enemySprite.setRotation(m_kinematic.m_orientation);
		t_window.draw(m_enemySprite);
		checkBound(t_window);
	}

	/*
	virtual void wander(sf::Vector2f& t_pos) {
		/*
		static sf::Clock wanderClock;
		static float wanderAngle = rand() % 360;

		if (wanderClock.getElapsedTime().asSeconds() >= 1.0f) {
			float angleChange = (rand() % 21 - 10) * (3.1415926575f / 180.0f);
			wanderAngle += angleChange * 100.0f;
			if (wanderAngle < 0) wanderAngle += 360;
			if (wanderAngle > 360) wanderAngle -= 360;

			std::cout << "wanderAngle: " << wanderAngle << std::endl;

			wanderClock.restart();
		}

		float radianAngle = wanderAngle * 3.1415926575f / 180.0f;
		m_kinematic.m_velocity = sf::Vector2f(cos(radianAngle), sin(radianAngle));

		float speedMultiplier = 0.5f;
		m_kinematic.m_velocity *= speedMultiplier;
		}
	}
	*/

	virtual void seek(sf::Vector2f& t_pos) {
		/*
		sf::Vector2f toTarget = t_pos - m_kinematic.m_pos;
		float distanceToTarget = sqrtf(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
		sf::Vector2f desiredVelocity = toTarget / distanceToTarget;
		float maxSpeed = 1.0f;
		float slowingRadius = 100.0f;

		float speed = maxSpeed;
		if (distanceToTarget < slowingRadius)
		{
			speed = maxSpeed * (distanceToTarget / slowingRadius);
		}

		// Scale the velocity to the calculated speed
		m_kinematic.m_velocity = desiredVelocity * speed;
		*/
	}
	

	
	virtual void flee(sf::Vector2f t_pos) {
		/*
		sf::Vector2f awayFromTarget = m_kinematic.m_pos - t_pos;
		float distanceToTarget = sqrt(awayFromTarget.x * awayFromTarget.x + awayFromTarget.y * awayFromTarget.y);
		sf::Vector2f desiredVelocity = awayFromTarget / distanceToTarget;
		float maxFleeSpeed = 0.5f;
		m_kinematic.m_velocity = desiredVelocity * maxFleeSpeed;
		*/
	}

protected:

	virtual void init() {
		m_enemyTexture.loadFromFile("Purple.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
	}

	void checkBound(sf::RenderWindow& t_window) {
		sf::FloatRect bounds = m_enemySprite.getGlobalBounds();
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

	virtual float getNewOrientation(float m_currentOrientation, sf::Vector2f& m_velocity)
	{
		if (std::abs(m_velocity.x) > 0 || std::abs(m_velocity.y) > 0)
		{
			return std::atan2(m_velocity.y, m_velocity.x) / 3.1415926535 * 180.0f;
		}
		else
		{
			return m_currentOrientation;
		}
	}

	Kinematic m_kinematic;

	sf::Texture m_enemyTexture; // texture used for sfml logo
	sf::Sprite m_enemySprite; // sprite used for sfml logo
	// sf::Vector2f m_curPos; // current position of player
	// sf::Vector2f m_velocity;

	float m_maxRotation = 10.0f;
	float m_maxSpeed = 1.0f;
};

class Wanderer : public Enemy {

public:
	Wanderer() {
		init();
	}

	virtual void wander(sf::Vector2f& t_pos) {
		static sf::Clock wanderClock;
		static float wanderAngle = rand() % 360;

		if (wanderClock.getElapsedTime().asSeconds() >= 2.0f) {
			m_kinematic.m_velocity = t_pos - m_kinematic.m_pos;
			m_kinematic.m_velocity /= sqrt(m_kinematic.m_velocity.x * m_kinematic.m_velocity.x
				+ m_kinematic.m_velocity.y * m_kinematic.m_velocity.y);
			m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);

			float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
			m_kinematic.m_orientation += m_maxRotation * randomRotation;

			m_kinematic.m_velocity = sf::Vector2f(-sin(m_kinematic.m_orientation), cos(m_kinematic.m_orientation)) * m_maxSpeed;
			// std::cout << "wander velocity: " << m_kinematic.m_velocity.x << " " << m_kinematic.m_velocity.y << std::endl;
		
			wanderClock.restart();
		}
	}

protected:
	virtual void init() {
		m_enemyTexture.loadFromFile("Walk.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
	}

};

#endif 
// !ENEMY_HPP