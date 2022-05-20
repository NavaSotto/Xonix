#include "Game.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include "SmartEnemy.h"
#include "NormalEnemy.h"
#include "Gift.h"
#include <iostream>

const sf::Vector2f SIZE_BUTTON(170.f, 170.f);
const int NUM_LEVELS = 4;
int Game::m_numLevel = 0;

Game::Game(sf::RenderWindow& window) :m_window(window), m_board(m_window)
{
	m_pacman = new Player(m_board.getPositionSquare({ 0,0 }));
	srand((unsigned int)time(NULL));
	ResourceManager::instance().getMusic("gameMusic")->play();

}

Game::~Game()
{

}

//manages the game structure
void Game::manageGame()
{
	toPlay();
	
}

//manages the levels in each game
void Game::toPlay()
{
	do
	{
		initilize();//craete ghosts and pacmans
		putNew();
		if (play()) //if its time to go to next level
		{
			m_board.initilize();
			std::cout << "www:" << m_pacman->getPosition().x << " " << m_pacman->getPosition().y << "\n";
			m_pacman->setPosition(m_board.getPositionSquare({ 0,0 }));
			std::cout <<"ttt:"<< m_pacman->getPosition().x << " " << m_pacman->getPosition().y << "\n";
			m_pacman->setScore(m_pacman->getScore() + (m_numLevel + 1) * 50);
		}
		else
			break;
	} while (m_numLevel <= NUM_LEVELS);

	end();

}

//initializes the players
void Game::initilize()
{
	m_timer.restart();
	m_numLevel++;//updates the level number
	m_enemy.clear();
	
	
	int option;
	for (int i = 0; i < Game::m_numLevel+2; i++)//adds ghosts according to level 
	{
		sf::Vector2i position = { 1+3*i ,m_board.size().x - 1 };
		option = random(4);
		switch (option)//add a ghost
		{
		case 0:
		case 1:m_enemy.push_back(std::make_shared< SmartEnemy>(m_board.getPositionSquare(position),position));
			break;
		case 2:
		case 3:m_enemy.push_back(std::make_shared< NormalEnemy>(m_board.getPositionSquare(position), position));
			break;
		}
	}

}




//Plays the game
bool Game::play()
{
	bool m_p = false;
	float delta_time= 0;
	while (Gift::total != 0 && getPacman()->getLives() != 0 ) //while you're still in the stage 
	{
		draw();

		for (unsigned int i = 0; i < m_enemy.size(); i++)  //moves and checks collide for each active object
		{

			if(delta_time>=0.2){
				m_enemy[i]->move(delta_time, (*this), m_board);
				delta_time = 0; //clock timer
			}
			delta_time += (float)m_timer.restart().asSeconds(); //clock timer
			handelEvent();

			draw();

			for (unsigned int k = 0; k < m_enemy.size(); k++)  //checks collide with all the other objects
				if (m_enemy[i]->crashObjects(m_enemy[k]->getObject(), m_enemy[i]->getLastSide()))
					m_enemy[i].get()->collide(m_enemy[k].get(), (*this));

			//m_board.draw(m_enemy, (*this));

			if (m_counter_time_health.getElapsedTime().asSeconds() >= 7)//set the new speed for 7 second if ate a poison cookie
				m_enemy[i]->setSpeed(DynamicObject::speed);

			if (m_counter_time_poison.getElapsedTime().asSeconds() >= 14) //set the new speed for 14 second if ate an health cookie
				m_enemy[i]->setSpeed(DynamicObject::speed);
			
			

		}

	}
	if (getPacman()->getLives() == 0) //if the pacmans live are finished the game is over
	{
		return false;
	}
	return true;//the level is ended
}
//locates all the active objects
void Game::putNew()
{
	//for (unsigned int i = 0; i < m_enemy.size(); i++)
	//m_enemy[i]->makePosition(m_board, (*this));//polimorphism that each one put himself in a good place
}

//ends the game and starts a new one
void Game::end()
{
	m_board.resetFile(); //closes & re-opens the file
	m_pacman = new Player(m_board.getPositionSquare({ 0,0 }));
	m_numLevel = 0;
	m_board.initilize();

	ResourceManager::instance().getPicture("gameOver");
	m_background.setSmooth(true);
	sf::Sprite background;
	background.setTexture(m_background);
	background.scale(Board::window_size.x / background.getGlobalBounds().width, Board::window_size.y / background.getGlobalBounds().height);

	m_window.draw(background);
	m_window.display();

	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))//waits for a press
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//if pressed to exit
		{
			return;
		}
	}
	toPlay(); //start the game again
}

//checks if the player pressed on the exit or resize button
void Game::handelEvent()
{
	if (m_window.isOpen())
	{
		for (sf::Event event; m_window.pollEvent(event);)
		{
			switch (event.type) //depends what user requested
			{
			case sf::Event::Resized:	//screen size change
			{
				sf::View newView(sf::Vector2f(m_window.getSize()) / 2.f,
					sf::Vector2f(m_window.getSize()));
				m_window.setView(newView);
				break;
			}
			case sf::Event::Closed:
				exit(0);
			case sf::Event::EventType::KeyPressed:
				m_pacman->move(event.key.code, m_board, m_enemy, *this);
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					screen('w');
					break;
				case sf::Keyboard::E:
					screen('e');
					break;
				
				}
			default:
					break;

			}
		}
	}
}




Player* Game::getPacman() const
{
	return m_pacman;//the user pacman 
}

std::vector<std::shared_ptr<DynamicObject>> Game::getGhosts() const
{
	return m_enemy;
}

//receives a location and checks if theres an object with this location
bool Game::ifInAcArry(sf::Vector2f place) const
{
	for (unsigned int i = 0; i < m_enemy.size(); i++)
		if (place == m_enemy[i]->getObject().getPosition())
			return true;
	return false;
}

//Removes a given active object from the vector
void Game::removeMe(std::shared_ptr<DynamicObject> active)
{
	for (unsigned int i = 0; i < m_enemy.size(); i++)
		if (m_enemy[i] == active)
		{
			removeCell(i);
			return;
		}
}

//removes a given cell number
void Game::removeCell(int whereto)
{
    //m_enemy[whereto].reset();
	m_enemy.erase(m_enemy.begin() + whereto);
}

void Game::draw()
{
	
	m_window.clear(sf::Color::Blue);
	m_board.draw(m_window);
	sf::Font font;
	font.loadFromFile("Toledo__.ttf"); //loading from an existing font

	sf::Text numOfLevel1;
	numOfLevel1.setPosition({960, 2 });
	numOfLevel1.setFont(font);
	numOfLevel1.setCharacterSize(75);
	//numOfLevel.setColor(sf::Color::Black);
	numOfLevel1.setString(static_cast<std::ostringstream*>(&(std::ostringstream() << m_numLevel))->str());
	m_window.draw(numOfLevel1);

	sf::Text numOfLevel2;
	numOfLevel2.setPosition({ 790, 2 });
	numOfLevel2.setFont(font);
	numOfLevel2.setCharacterSize(75);
	//numOfLevel.setColor(sf::Color::Black);
	numOfLevel2.setString(static_cast<std::ostringstream*>(&(std::ostringstream() << "level-"))->str());
	m_window.draw(numOfLevel2);
	//********************************************************
	//setting the lives display
	sf::Text lives1;
	sf::Text lives2;
	lives1.setPosition({ 1, 4 });
	lives1.setFont(font);
	lives1.setCharacterSize(50);
	//	lives.setColor(sf::Color::Black);
	lives1.setString(static_cast<std::ostringstream*>(&(std::ostringstream() <<m_pacman->getLives()))->str());
	m_window.draw(lives1);

	lives2.setPosition({ 101, 4 });
	lives2.setFont(font);
	lives2.setCharacterSize(50);
	//	lives.setColor(sf::Color::Black);
	lives2.setString(static_cast<std::ostringstream*>(&(std::ostringstream() << "lives"))->str());
	m_window.draw(lives2);

	//********************************************************

	//setting the score display
	sf::Text score1;
	score1.setPosition({ 250,4 });
	score1.setFont(font);
	score1.setCharacterSize(50);
	//	score.setColor(sf::Color::Black);
	score1.setString(static_cast<std::ostringstream*>(&(std::ostringstream() <<m_pacman->getScore()))->str());
	m_window.draw(score1);


	sf::Text score2;
	score2.setPosition({ 350,4 });
	score2.setFont(font);
	score2.setCharacterSize(50);
	//	score.setColor(sf::Color::Black);
	score2.setString(static_cast<std::ostringstream*>(&(std::ostringstream() <<"score"))->str());
	m_window.draw(score2);

	//********************************************************




	for (unsigned int i = 0; i < m_enemy.size(); i++)
		m_window.draw(m_enemy[i]->getObject());
	m_window.draw(m_pacman->getObject());
	m_window.display();
}

void Game::resetm_counter_time_poison()
{
	m_counter_time_poison.restart();
}

void Game::reset_counter_time_health()
{
	m_counter_time_health.restart();
}

std::vector<sf::Vector2i> Game::getEnemyPosition()
{
	std::vector<sf::Vector2i> v;
	for (auto i : m_enemy)
		v.push_back(i->getBoardPosition());
	return v;
}




void  Game::screen(char c) 
{
	sf::RenderWindow  window(sf::VideoMode(1000, 800), "GAME");
	sf::Event event;
	sf::Texture t;

	switch (c)
	{
	case 'w':
		t = ResourceManager::instance().getPicture("winnerScreen");
		break;
	case 'e':
		t = ResourceManager::instance().getPicture("gameOver");
		break;
	default:
		break;
	}
	sf::Sprite s;
	s.setTexture(t);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		window.clear();
		window.draw(s);
		window.display();
	}
}



void  Game::endScreen()
{
	sf::RenderWindow  game_over_window(sf::VideoMode(1000, 800), "gameOver");
	sf::Event event;
	while (game_over_window.isOpen())
	{
		while (game_over_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				game_over_window.close();
				break;
			default:
				break;
			}
		}
		sf::Texture t = ResourceManager::instance().getPicture("gameOver");
		sf::Sprite s;
		s.setTexture(t);
		game_over_window.clear();
		game_over_window.draw(s);
		game_over_window.display();
	}
}

//-------A function which picks a random number between 0 and the limit.
int random(int limit)
{
	int v = rand() % limit;
	return (v);
}
