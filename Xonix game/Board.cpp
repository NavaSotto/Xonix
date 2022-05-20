#include "Board.h"
#include "Game.h"
#include "wall.h"
#include "Gift.h"
#include "IncreaseSpeed.h"
#include "IncreaseLives.h"
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include<string>
#include <memory>

sf::Vector2f Board::window_size = { 1000, 800 };
sf::Vector2f Board::cubicle_size;
int Board::num_rows;
int Board::num_cols;


Board::Board(sf::RenderWindow& window) :m_window(window), m_findEnemy(false)
{
	
	m_Background = ResourceManager::instance().getPicture("levelScreen");
	m_Background.setSmooth(true);

	m_myfile.open("Board.txt");
	initilize();  //creates the board from the text file
}

Board::~Board()
{
	m_myfile.close();

}

std::vector<std::shared_ptr<StaticObject>> Board::getP() const
{
	return m_pObjects;
}

void Board::initilize()
{/*
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		 m_pObjects[i].reset();*/
	m_pObjects.clear();
	std::string line;
	if (m_myfile.is_open())
	{
		getline(m_myfile, line);	//Read a line.
		num_rows = atoi(line.c_str());//reads the number of rows

		getline(m_myfile, line);
		num_cols = atoi(line.c_str());  //reads the number of columns

		window_size = { (float)(window_size.x), (float)(window_size.y) };//saves the window's size  
		cubicle_size = { window_size.x / num_cols ,(window_size.y - 50) / num_rows };//calculates accordingly the cubicle size

		build(cubicle_size, num_rows, num_cols);
		int picked = 0;  //will be picked randomly to decide what type 
		for (int i = 0; i < num_rows; i++)
		{
			for (int j = 0; j < num_cols; j++)
			{
				char c = m_myfile.get();
				switch (c)
				{
				
				case ('*'):  //if its a cookie
				{
					picked = random(2);
					switch (picked)
					{
					case 0:
						m_pObjects.push_back(std::make_shared<IncreaseSpeed>(c, sf::Vector2f((cubicle_size.x)*j,(cubicle_size.y)*i + 50 )));
						break;
					case 1:
						m_pObjects.push_back(std::make_shared<IncreaseLives>(c, sf::Vector2f( (cubicle_size.x)*j,(cubicle_size.y)*i + 50 )));
						break;
					}
				}break;
				}
			}
			m_myfile.get();
		}
	}
}

void Board::resetFile()   //when starts the game again we need to read the file from the beginning
{
	m_myfile.close();
	m_myfile.open("Board.txt");
}

//Will draw the board
void Board::draw(sf::RenderWindow& m_window)//the main window
{
	sf::Sprite m_backgrounds;
	m_backgrounds.setTexture(m_Background);
	m_backgrounds.scale(Board::window_size.x / m_backgrounds.getGlobalBounds().width, Board::window_size.y / m_backgrounds.getGlobalBounds().height);

	m_backgrounds.setTexture(m_Background);
	m_window.draw(m_backgrounds);
	for (unsigned int i = 0; i < m_board.size(); i++)
		for (unsigned int j = 0; j < m_board[i].size(); j++)
			m_board[i][j].drawObject(m_window);
			
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		m_window.draw(m_pObjects[i]->getObject());



}



//Removes a given passive object from the vector
void Board::removeMe(StaticObject* passive)
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		if (m_pObjects[i].get() == passive)
		{
			removeCell(i);
			return;
		}
}

//removes a given cell number
void Board::removeCell(int whereto)
{
	m_pObjects.erase(m_pObjects.begin() + whereto);
}

//receives a location and checks if theres an object with this location
bool Board::ifInPArry(sf::Vector2f place) const
{
	for (unsigned int i = 0; i < m_pObjects.size(); i++)
		if (place == m_pObjects[i]->getObject().getPosition())
			return true;
	return false;
}



void Board::build(sf::Vector2f sizeOfSquare, int sizeRows, int sizeColumns)
{
	m_board.resize(sizeRows);
	for (int i = 0; i < sizeRows; i++)
		for (int j = 0; j < sizeColumns; j++) {
			if (i == 0 || i == sizeRows - 1 || j == 0 || j == sizeColumns - 1)
				m_board[i].push_back(Square{ sf::Vector2f{ (float)j*sizeOfSquare.x,(float)i*sizeOfSquare.y + 50 }, sizeOfSquare,ICE });
			else
				m_board[i].push_back(Square{ sf::Vector2f{ (float)j*sizeOfSquare.x,(float)i*sizeOfSquare.y + 50 }, sizeOfSquare,EMPTY });
		}
}

sf::Vector2i Board::size()
{
	return sf::Vector2i(m_board.size(), m_board[0].size());
}

void Board::setSquare(sf::Vector2i p, square_mode s)
{
	m_board[p.y][p.x].setSquare(s);
}

sf::Vector2f Board::getPositionSquare(sf::Vector2i v)
{
	return m_board[v.y][v.x].getPosition();
}

square_mode Board::getModeSquare(sf::Vector2i v)
{
	return m_board[v.y][v.x].getMode();
}

sf::Vector2f Board::getSizeSquare()
{
	return { m_board[0][0].getObject().getGlobalBounds().height,m_board[0][0].getObject().getGlobalBounds().width };
}

void Board::close(sf::Vector2i begin, sf::Vector2i end, std::vector<std::shared_ptr<DynamicObject>> enemy)
{
	if (begin.x == end.x) {
		check({ begin.x - 1,begin.y }, enemy);
		if (m_findEnemy) {
			m_findEnemy = false;
			check({ begin.x + 1,begin.y }, enemy);
		}
	}

	else if (begin.y == end.y) {
		check({ begin.x ,begin.y - 1 }, enemy);
		if (m_findEnemy) {
			m_findEnemy = false;
			check({ begin.x ,begin.y + 1 }, enemy);
		}
	}
	if (!m_findEnemy)
		setClose();
}

void Board::setClose()
{
	for (int i = 1; i < m_board.size()-1; i++)
		for (int j = 1; j < m_board[i].size()-1; j++) {
			if (m_board[i][j].getCover() || m_board[i][j].getMode() == RUN) {
				m_board[i][j].setSquare(CLOSE);		
			}
			m_board[i][j].setCover(false);	
		}
}

bool Board::check(sf::Vector2i point, std::vector<std::shared_ptr<DynamicObject>> enemy)
{
	for (auto i : enemy) {
		if (point == i->getBoardPosition()) {
			for (int i = 1; i < m_board.size() - 1; i++)
				for (int j = 1; j < m_board[i].size() - 1; j++) {
					m_board[i][j].setCover(false);
				}
			m_findEnemy = true;
			return false;
		}
		
	}
	//std::cout << "point" << point.x << point.y << "\n";
	m_board[point.y][point.x].setCover(true);
	if (canCheck({ point.x ,point.y - 1 }))
		check({ point.x, point.y - 1 },enemy);	
	if (canCheck({ point.x ,point.y + 1 })) 
		check({ point.x, point.y + 1 }, enemy);	
	if (canCheck({ point.x - 1 ,point.y })) 
		check({ point.x - 1, point.y }, enemy);
	if (canCheck({ point.x + 1 ,point.y })) 
		check({ point.x + 1, point.y }, enemy);

	return true;
}

bool Board::isInRang(sf::Vector2i v)
{
	return v.x>0&&v.x<m_board.size()-1&&v.y>0&&v.y<m_board[0].size()-1;
}

bool Board::canCheck(sf::Vector2i v)
{
	return isInRang({ v.x ,v.y }) && m_board[v.y][v.x].getMode() == EMPTY && !m_board[v.y][v.x].getCover()&&!m_findEnemy;
}
