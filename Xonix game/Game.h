#pragma once
#include "DynamicObject.h"
#include "Player.h"
#include "Board.h"
#include <SFML/Audio.hpp>

#include "ResourceManager.h"
#include <fstream>
#include <sstream>
class Game
{


public:
	static int m_numLevel;//saves the current num of level

	Game(sf::RenderWindow& window);
	~Game();

	Player* getPacman() const;//return the user
	std::vector<std::shared_ptr<DynamicObject>> getGhosts() const;//return the players' vector 
	bool ifInAcArry(sf::Vector2f) const;
	//return if the object with the givin position is in the vector 
	void screen(char key);
	void  endScreen();


	void manageGame();
	void initilize();//initilize the tools of the game
	bool play();//the main function of the game
	void toPlay();//the loop of the levels
	void putNew();//putting the players in their start place 
	void end();//restart and end the game
	void handelEvent();

	void removeMe(std::shared_ptr<DynamicObject>);
	void removeCell(int);
	void draw();
	void resetm_counter_time_poison();
	void reset_counter_time_health();
	std::vector<sf::Vector2i> getEnemyPosition();
private:
	std::vector<std::shared_ptr<DynamicObject>> m_enemy;//the user
	Player* m_pacman;//the players
	Board m_board;//the board
	sf::RenderWindow &m_window;//the main window
	sf::Texture m_background;
	sf::Texture m_play;
	sf::Texture m_exit;

	sf::Clock m_counter_time_health;//count time to the health cookie
	sf::Clock m_counter_time_poison;//count time to the poison cookie
	sf::Clock m_timer;//the main timer of the game

	sf::Music m_music;

};
int random(int);//random a number from 0 to the givin limit

