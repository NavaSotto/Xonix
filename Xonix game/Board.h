#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include "Square.h"
#include <fstream>
#include <memory>

class Board
{
public:
	//constructor
	Board(sf::RenderWindow& window);
	//distructor
	~Board();

	//static values
	static sf::Vector2f cubicle_size;//the size of a cubicle 
	static sf::Vector2f window_size;//the size of the window
	static int num_rows;
	static int num_cols;

	void initilize();//build the board from the file text
	void resetFile();//reset the files in the end of the game

	void removeMe(StaticObject*);//remove the passive object from the vector
	void removeCell(int);//remove a specific cell in the vector

	void draw(sf::RenderWindow& m_window);//the main window);


	bool ifInPArry(sf::Vector2f) const;//return if the object with the givin position is in the vector 

	//sf::RenderWindow& getWindow();//return the window
	std::vector<std::shared_ptr<StaticObject>> getP() const;//return the passive's vector

	void build(sf::Vector2f sizeOfSquare, int sizeRows, int sizeColumns);
	sf::Vector2i size();
	void setSquare(sf::Vector2i, square_mode);
	sf::Vector2f getPositionSquare(sf::Vector2i);
	square_mode getModeSquare(sf::Vector2i);
	sf::Vector2f getSizeSquare();
	void close(sf::Vector2i begin, sf::Vector2i end, std::vector<std::shared_ptr<DynamicObject>> enemy);
	void setClose();
	bool check(sf::Vector2i, std::vector<std::shared_ptr<DynamicObject>> enemy);
	bool isInRang(sf::Vector2i);
	bool canCheck(sf::Vector2i);

private:
	sf::RenderWindow &m_window;//the main window
	sf::Texture m_Background;
	std::vector<std::shared_ptr<StaticObject>> m_pObjects;//the passive objects
	std::ifstream m_myfile;//Board.txt
	std::vector < std::vector<Square>> m_board;
	bool m_findEnemy;
};

