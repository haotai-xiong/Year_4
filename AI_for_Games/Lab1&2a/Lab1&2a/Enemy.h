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
		setupSprite();

		// init pos
		m_kinematic.m_pos = sf::Vector2f(rand() % 1920, rand() % 1080);
		m_enemySprite.setPosition(m_kinematic.m_pos);

		// init velocity
		m_kinematic.m_velocity = sf::Vector2f(static_cast <float> (rand()) / static_cast<float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX)
			, static_cast<float>(rand()) / static_cast <float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX));
	}

	void update(sf::Time t_deltaTime) {
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

	void render(sf::RenderWindow& t_window)	{
		t_window.draw(m_enemySprite);
		checkBound(t_window);
	}

	void wander() {
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

	void seek(sf::Vector2f& t_pos)
	{
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
	}

	void flee(sf::Vector2f t_pos)
	{
		sf::Vector2f awayFromTarget = m_kinematic.m_pos - t_pos;
		float distanceToTarget = sqrt(awayFromTarget.x * awayFromTarget.x + awayFromTarget.y * awayFromTarget.y);
		sf::Vector2f desiredVelocity = awayFromTarget / distanceToTarget;
		float maxFleeSpeed = 0.5f;
		m_kinematic.m_velocity = desiredVelocity * maxFleeSpeed;
	}

private:

	void setupSprite() {
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

	Kinematic m_kinematic;

	sf::Texture m_enemyTexture; // texture used for sfml logo
	sf::Sprite m_enemySprite; // sprite used for sfml logo
	// sf::Vector2f m_curPos; // current position of player
	// sf::Vector2f m_velocity;
};

#endif // !ENEMY_HPP