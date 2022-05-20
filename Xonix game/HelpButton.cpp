#include "HelpButton.h"
#include "ResourceManager.h"


HelpButton::HelpButton(const sf::Font& font, const sf::Vector2f position)
{
	m_button.setFont(font);
	m_button.setCharacterSize(55);
	m_button.setPosition(position);
	m_button.setFillColor(sf::Color::White);
	m_button.setOutlineColor(sf::Color::Red);
	m_button.setOutlineThickness(4);
	m_button.setString("HELP");
}


HelpButton::~HelpButton()
{
}

void HelpButton::execute(sf::RenderWindow & m_window)
{
	sf::RenderWindow  help_window(sf::VideoMode(1000, 800), "help_window");
	sf::Event event;
	while (help_window.isOpen())
	{
		while (help_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				help_window.close();
				break;
			}
		}
	sf::Texture t = ResourceManager::instance().getPicture("helpScreen");
	sf::Sprite s;
	s.setTexture(t);
	help_window.clear();
	help_window.draw(s);
	help_window.display();
    }
}
