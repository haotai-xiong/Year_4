#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy()
	{
		setupSprite();

		// init pos
		m_curPos = sf::Vector2f(1000.0f, 500.0f);
		m_enemySprite.setPosition(m_curPos);

		// init velocity
		m_velocity = sf::Vector2f(static_cast <float> (rand()) / static_cast<float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX)
			, static_cast<float>(rand()) / static_cast <float>(RAND_MAX) - static_cast<float>(rand()) / static_cast <float>(RAND_MAX));
	}

	void update(sf::Time t_deltaTime)
	{
		m_curPos += m_velocity;
		m_enemySprite.setPosition(m_curPos);
	}

	void render(sf::RenderWindow& t_window)
	{
		t_window.draw(m_enemySprite);
		checkBound(t_window);
	}

private:

	void setupSprite()
	{
		m_enemyTexture.loadFromFile("Purple.png");
		m_enemyTexture.setSmooth(true);
		m_enemySprite.setTexture(m_enemyTexture);
	}

	void checkBound(sf::RenderWindow& t_window)
	{
		sf::FloatRect bounds = m_enemySprite.getGlobalBounds();
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

	sf::Texture m_enemyTexture; // texture used for sfml logo
	sf::Sprite m_enemySprite; // sprite used for sfml logo
	sf::Vector2f m_curPos; // current position of player
	sf::Vector2f m_velocity;
};

#endif // !ENEMY_HPP