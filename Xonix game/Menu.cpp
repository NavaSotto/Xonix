#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "HelpButton.h"
#include "PlayButton.h"
#include "ExitButton.h"
#include "ResourceManager.h"

Menu::Menu():m_window(sf::VideoMode(1000, 800), "XONIX")
{
	m_font.loadFromFile("Toledo__.ttf");
	m_option.emplace_back(std::make_unique<PlayButton>
		(m_font, sf::Vector2f{ m_window.getSize().x / float(4), m_window.getSize().y / (m_max + 1) *float(1) }));
	m_option.emplace_back(std::make_unique<HelpButton>
		(m_font, sf::Vector2f{ m_window.getSize().x / float(4), m_window.getSize().y / (m_max + 1) *float(1.8) }));
	m_option.emplace_back(std::make_unique<ExitButton>
		(m_font, sf::Vector2f{ m_window.getSize().x / float(4), m_window.getSize().y / (m_max + 1) *float(2.6) }));

	

	m_backTexture = ResourceManager::instance().getPicture("openScreen");
	m_backSprite.setTexture(m_backTexture);
	m_backSprite.scale(sf::Vector2f((float)1000 / m_backTexture.getSize().x, (float)800 / m_backTexture.getSize().y));
	

	m_index = 0;
	m_option[m_index]->setFillColor(sf::Color::White);
	m_option[m_index]->setOtlineColor(sf::Color::Red);
	m_option[m_index]->setFillColor(sf::Color::Black);
}

void Menu::openMenu()
{
	ResourceManager::instance().getMusic("playMusic")->play();

	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					manageMenu();
					break;
				}
			}
		}

		m_window.clear();
		m_window.draw(m_backSprite);
		//draw();
		m_window.display();
	}
}
	


void Menu::manageMenu()
{
	m_backTexture = ResourceManager::instance().getPicture("menuScreen");
	m_backSprite.setTexture(m_backTexture);
	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					moveUp();
					break;
				case sf::Keyboard::Down:
					moveDown();
					break;
				case sf::Keyboard::Return:
					m_option[m_index]->setFillColor(sf::Color::White);
					m_option[m_index]->execute(m_window);
					break;
				}
			}
		}

		m_window.clear();
		m_window.draw(m_backSprite);
		draw();
		m_window.display();
	}
}

void Menu::draw()
{

	for (int i = 0; i < m_option.size(); i++)
		m_option[i]->draw(m_window);
}

void Menu::moveUp()
{
	if (m_index - 1 >= 0)
	{
		m_option[m_index]->setFillColor(sf::Color::White);
		m_option[m_index]->setOtlineColor(sf::Color::Red);
		m_index--;
		m_option[m_index]->setFillColor(sf::Color::Black);

	}
}

void Menu::moveDown()
{

	if (m_index + 1 <m_max)
	{
		m_option[m_index]->setFillColor(sf::Color::White);
		m_option[m_index]->setOtlineColor(sf::Color::Red);
		m_index++;
		m_option[m_index]->setFillColor(sf::Color::Black);
	}
}

