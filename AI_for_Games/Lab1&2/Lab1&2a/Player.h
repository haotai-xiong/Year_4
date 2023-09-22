#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player()
	{
		setupSprite();

		// init pos
		m_curPos = sf::Vector2f(500.0f, 500.0f);
		m_playerSprite.setPosition(m_curPos);

		// init velocity
		m_velocity = sf::Vector2f(static_cast <float> (rand())/static_cast<float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX)
			, static_cast<float>(rand())/static_cast <float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX));
	}

	void processKeys(sf::Event t_event)
	{
		if (sf::Keyboard::Up == t_event.key.code) {
			m_velocity *= m_increment;
		}
		else if (sf::Keyboard::Down == t_event.key.code) {
			m_velocity /= m_increment;
		}
	}

	void update(sf::Time t_deltaTime)
	{
		m_curPos += m_velocity;
		m_playerSprite.setPosition(m_curPos);
		
		// m_shape.setPosition(m_curPos);
	}

	void render(sf::RenderWindow& t_window)
	{
		t_window.draw(m_playerSprite);
		checkBound(t_window);
		// t_window.draw(m_shape);
	}

	sf::Vector2f& getPos() { return m_curPos; }

private:

	void setupSprite()
	{
		// system("dir");

		m_playerTexture.loadFromFile("Blue.png");
		m_playerTexture.setSmooth(true);
		m_playerSprite.setTexture(m_playerTexture);
		m_playerSprite.setOrigin(sf::Vector2f(m_playerSprite.getGlobalBounds().width / 2.0f,
			m_playerSprite.getGlobalBounds().height / 2.0f));

		/*
		m_shape.setRadius(25.0f);
		m_shape.setFillColor(sf::Color(150, 50, 250));
		m_shape.setOutlineThickness(2);
		m_shape.setOutlineColor(sf::Color(250, 150, 100));
		*/
	}

	void checkBound(sf::RenderWindow& t_window)
	{
		sf::FloatRect bounds = m_playerSprite.getGlobalBounds();
		float windowWidth = static_cast<float>(t_window.getSize().x);
		float windowHeight = static_cast<float>(t_window.getSize().y);

		// Wrap horizontally
		if (m_curPos.x + bounds.width < 0) {
			m_curPos.x = windowWidth;
		}
		else if (m_curPos.x > windowWidth) {
			m_curPos.x = -bounds.width;
		}

		// Wrap vertically
		if (m_curPos.y + bounds.height < 0) {
			m_curPos.y = windowHeight;
		}
		else if (m_curPos.y > windowHeight) {
			m_curPos.y = -bounds.height;
		}
	}

	sf::CircleShape m_shape;
	sf::Texture m_playerTexture; // texture used for sfml logo
	sf::Sprite m_playerSprite; // sprite used for sfml logo
	sf::Vector2f m_curPos; // current position of player
	sf::Vector2f m_velocity;

	float m_increment = 1.03f;
};

#endif // !PLAYER_HPP

