#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Behavior.h"
#define PI 3.1415926535

//-------------------------------------------------------------------------------------------------------------
// Default Enemy Class
//-------------------------------------------------------------------------------------------------------------
class Enemy {
public:
	Enemy() {
		init();
	}

	virtual void update(sf::Time t_deltaTime) {
		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

	virtual void render(sf::RenderWindow& t_window, sf::Vector2f& t_playerPos)	{
		drawVelocityDirection(t_window, m_kinematic.m_pos, m_kinematic.m_velocity);
		m_enemySprite.setRotation(getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity));
		t_window.draw(m_enemySprite);
		checkBound(t_window);

		drawVisionCone(t_window, t_playerPos);

		m_text.setPosition(m_kinematic.m_pos.x, m_kinematic.m_pos.y + 50);  // Adjust the offset as needed
		t_window.draw(m_text);
	}

protected:

	virtual void init() {
		m_enemyTexture.loadFromFile("Purple.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));
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

	virtual float getNewOrientation(float m_currentOrientation, sf::Vector2f& m_velocity) {
		if (std::abs(m_velocity.x) > 0 || std::abs(m_velocity.y) > 0)
		{
			return std::atan2(m_velocity.y, m_velocity.x) / PI * 180.0f;
		}
		else
		{
			return m_currentOrientation;
		}
	}

	void drawVisionCone(sf::RenderWindow& t_window, sf::Vector2f& t_pos) {
			sf::ConvexShape visionCone;
			visionCone.setPointCount(3);
			visionCone.setPoint(0, m_kinematic.m_pos);
			visionCone.setPoint(1, sf::Vector2f(m_kinematic.m_pos.x + std::cos((m_kinematic.m_orientation - m_steering.degree) * PI / 180.0f) * m_steering.m_visionConeLength,
				m_kinematic.m_pos.y + std::sin((m_kinematic.m_orientation - m_steering.degree) * PI / 180.0f) * m_steering.m_visionConeLength));
			visionCone.setPoint(2, sf::Vector2f(m_kinematic.m_pos.x + std::cos((m_kinematic.m_orientation + m_steering.degree) * PI / 180.0f) * m_steering.m_visionConeLength,
				m_kinematic.m_pos.y + std::sin((m_kinematic.m_orientation + m_steering.degree) * PI / 180.0f) * m_steering.m_visionConeLength));

			sf::Vector2f toPlayer = t_pos - m_kinematic.m_pos;
			float lengthToPlayer = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
			float angleToPlayer = angleBetweenVectors(m_kinematic.m_pos, t_pos);

			if (angleToPlayer <= m_steering.degree && angleToPlayer >= -m_steering.degree && lengthToPlayer < m_steering.m_visionConeLength) {
				visionCone.setFillColor(sf::Color(255, 0, 0, 50));
				std::cout << angleToPlayer << std::endl;
			}
			else {
				visionCone.setFillColor(sf::Color(255, 255, 0, 50));
			}

			// Draw the vision cone
			t_window.draw(visionCone);
	}
	
	float angleBetweenVectors(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
			float dotProduct = vec1.x * vec2.x + vec1.y * vec2.y;
			float magnitude1 = std::sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
			float magnitude2 = std::sqrt(vec2.x * vec2.x + vec2.y * vec2.y);
			float angleInRadians = std::acos(dotProduct / (magnitude1 * magnitude2));
			std::cout << magnitude1 << std::endl;
			return angleInRadians * 180.0f / PI;
	}

	void drawVelocityDirection(sf::RenderWindow& t_window, const sf::Vector2f& t_pos, const sf::Vector2f& t_velocity) {
		if (t_velocity.x == 0.0f && t_velocity.y == 0.0f) {
			return;
		}

		sf::VertexArray line(sf::Lines, 2);

		line[0].position = t_pos;
		line[0].color = sf::Color::Red;
		sf::Vector2f normalizedVelocity = t_velocity / std::sqrt(t_velocity.x * t_velocity.x + t_velocity.y * t_velocity.y);
		line[1].position = t_pos + normalizedVelocity * 250.0f;
		line[1].color = sf::Color::Red;

		t_window.draw(line);
	}

	Kinematic m_kinematic;
	Steering m_steering;

	sf::Texture m_enemyTexture; // texture used for sfml logo
	sf::Sprite m_enemySprite; // sprite used for sfml logo
	sf::Color m_visionConeColor;
	sf::Vector2f desiredVelocity;
	Behavior m_behaviorPattern;

	sf::Text m_text;
	sf::Font m_font;
};

//-------------------------------------------------------------------------------------------------------------
// Wander Class
//-------------------------------------------------------------------------------------------------------------
class Wanderer : public Enemy {
public:
	Wanderer() {
		init("Wander");
	}

	virtual void update(sf::Time t_deltaTime, sf::Vector2f& t_playerPos, Kinematic& t_playerKinematic) {
		m_behaviorPattern.process(Type::wander, m_kinematic, m_steering, t_playerPos, t_playerKinematic);

		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

protected:
	virtual void init(std::string t_string) {
		m_enemyTexture.loadFromFile("Walk.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		m_font.loadFromFile("Freedom-10eM.ttf");
		m_text.setFont(m_font);
		m_text.setCharacterSize(24);
		m_text.setString(t_string);
		m_text.setFillColor(sf::Color::White);

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}

};

//-------------------------------------------------------------------------------------------------------------
// Seek Class
//-------------------------------------------------------------------------------------------------------------
class Seeker : public Enemy {
public:
	Seeker() {
		init("Seeker");
	}

	virtual void update(sf::Time t_deltaTime, sf::Vector2f& t_playerPos, Kinematic& t_playerKinematic) {
		m_behaviorPattern.process(Type::seeker, m_kinematic, m_steering, t_playerPos, t_playerKinematic);

		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

protected:
	virtual void init(std::string t_string) {
		m_enemyTexture.loadFromFile("Slide.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		m_font.loadFromFile("Freedom-10eM.ttf");
		m_text.setFont(m_font);
		m_text.setCharacterSize(24);
		m_text.setString(t_string);
		m_text.setFillColor(sf::Color::White);

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
};

//-------------------------------------------------------------------------------------------------------------
// Arrive Slow Class
//-------------------------------------------------------------------------------------------------------------
class ArriveSlower : public Enemy {
public:
	ArriveSlower() {
		init("ArriveSlower");
	}

	virtual void update(sf::Time t_deltaTime, sf::Vector2f& t_playerPos, Kinematic& t_playerKinematic) {
		m_behaviorPattern.process(Type::arriveSlow, m_kinematic, m_steering, t_playerPos, t_playerKinematic);

		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

protected:
	virtual void init(std::string t_string) {
		m_enemyTexture.loadFromFile("Slide.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		m_font.loadFromFile("Freedom-10eM.ttf");
		m_text.setFont(m_font);
		m_text.setCharacterSize(24);
		m_text.setString(t_string);
		m_text.setFillColor(sf::Color::White);

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
};

//-------------------------------------------------------------------------------------------------------------
// Arrive Fast Class
//-------------------------------------------------------------------------------------------------------------
class ArriveFaster : public Enemy {
public:
	ArriveFaster() {
		init("ArriveSlower");
	}

	virtual void update(sf::Time t_deltaTime, sf::Vector2f& t_playerPos, Kinematic& t_playerKinematic) {
		m_behaviorPattern.process(Type::arriveFast, m_kinematic, m_steering, t_playerPos, t_playerKinematic);

		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

protected:
	virtual void init(std::string t_string) {
		m_enemyTexture.loadFromFile("Slide.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		m_font.loadFromFile("Freedom-10eM.ttf");
		m_text.setFont(m_font);
		m_text.setCharacterSize(24);
		m_text.setString(t_string);
		m_text.setFillColor(sf::Color::White);

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
};

//-------------------------------------------------------------------------------------------------------------
// Pursue Class
//-------------------------------------------------------------------------------------------------------------
class Pursuer : public Enemy {
public:
	Pursuer() {
		init("Pursue");
	}

	virtual void update(sf::Time t_deltaTime, sf::Vector2f& t_playerPos, Kinematic& t_playerKinematic) {
		m_behaviorPattern.process(Type::pursue, m_kinematic, m_steering, t_playerPos, t_playerKinematic);

		m_kinematic.m_velocity += m_steering.m_linear;
		m_kinematic.m_pos += m_kinematic.m_velocity;
		m_kinematic.m_orientation = getNewOrientation(m_kinematic.m_orientation, m_kinematic.m_velocity);
		m_enemySprite.setPosition(m_kinematic.m_pos);
	}

protected:
	virtual void init(std::string t_string) {
		m_enemyTexture.loadFromFile("Dead.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		m_font.loadFromFile("Freedom-10eM.ttf");
		m_text.setFont(m_font);
		m_text.setCharacterSize(24);
		m_text.setString(t_string);
		m_text.setFillColor(sf::Color::White);

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
};

class Fleer : public Enemy {
public:
	Fleer() {
		init();
	}

	void flee(sf::Vector2f& t_pos) {
		sf::Vector2f awayFromTarget = m_kinematic.m_pos - t_pos;
		float distanceToTarget = sqrt(awayFromTarget.x * awayFromTarget.x + awayFromTarget.y * awayFromTarget.y);
		sf::Vector2f desiredVelocity = awayFromTarget / distanceToTarget;
		float maxFleeSpeed = 0.5f;
		m_kinematic.m_velocity = desiredVelocity * maxFleeSpeed;
	}

protected:
	virtual void init() {
		m_enemyTexture.loadFromFile("Dead.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
		m_enemySprite.setOrigin(sf::Vector2f(m_enemySprite.getGlobalBounds().width / 2.0f,
			m_enemySprite.getGlobalBounds().height / 2.0f));

		int x = rand() % 1921; // Range [0, 1920]
		int y = rand() % 1081; // Range [0, 1080]
		m_kinematic.m_pos = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
};

#endif 
// !ENEMY_HPP