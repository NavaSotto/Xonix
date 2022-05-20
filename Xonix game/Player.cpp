#include "Player.h"
#include "Game.h"
#include <memory>

const int LIVES = 3;

Player::Player(sf::Vector2f place) : DynamicObject(place)
{
	m_texture = ResourceManager::instance().getPicture("player");
	m_object.setTexture(m_texture);
	
	m_object.scale({ Board::cubicle_size.x / m_object.getGlobalBounds().width,Board::cubicle_size.y / m_object.getGlobalBounds().height });

	m_score = 0;
	m_lives = LIVES;

	ResourceManager::instance().getMusic("gameMusic")->play();

}


int Player::getLives() const
{
	return m_lives;
}

void Player::setLives(int l)
{
	m_lives = l;
}

//collide by double dispatch
void Player::collide(DynamicObject* other, Game& control)
{
	other->collide(this, control);
}

void Player::collide(Player * other, Game& theGame)
{
}

//collide with a ghost
void Player::collide(Enemy* ghost, Game& control)
{
	setLives(getLives() - 1);
	///*if (dynamic_cast<Player*>(this))
	//	if (m_lives == 0)                               //not working
	//		control.removeMe(this);*/
	control.putNew();//put new
}

//coliide with passive objects
void Player::collide(StaticObject* other, Game& control, Board& board, sf::Vector2f oldPlace)
{
	if (crashObjects(other->getObject(), m_last_side)) //If theres a type 1 crash - that there's a common point between two objects.
	{
		if (dynamic_cast<Wall*>(other))
		{
			if (m_lastPos != 4)  //saves from what side it crashed into the walls
				m_last_side = m_lastPos;
			m_lastPos = 4;
			m_object.setPosition({ oldPlace.x, oldPlace.y }); //returns to the last position
			return;//not remove the walls
		}

	}

	if (crashObjectsBorder(other->getObject(), m_last_side)) //if crashed into a cookie
	{
		if (dynamic_cast<IncreaseSpeed*>(other))
		{
			control.reset_counter_time_health();
			cookieCrash(IncreaseSpeed::m_SpeedIncrease, control); //increases speed accordingly
			board.removeMe(other);//deletes the cookie
			//sf::Vector2i v = { (int)other->getPosition().x,(int)other->getPosition().y };
			//board.setSquare(v, EMPTY);
			return;
		}
		if (dynamic_cast<IncreaseLives*>(other))
		{
			control.resetm_counter_time_poison();
			cookieCrash(IncreaseLives::m_speedIncreased, control); //decreases the speed accordingly
			board.removeMe(other);//deletes the cookie
			/*sf::Vector2i v = { (int)other->getPosition().x,(int)other->getPosition().y };
			board.setSquare(v, EMPTY);*/
			return;
		}
		if (dynamic_cast<Gift*>(other))
		{
			cookieCrash(Gift::m_speedIncrease, control);
			board.removeMe(other);//remove the cookie from the vector of the passives
			/*sf::Vector2i v = { (int)other->getPosition().x,(int)other->getPosition().y };
			board.setSquare(v, EMPTY);*/
			return;
		}
	}
	return;
}

void Player::makePosition(Board & board, Game& control)
{
	int begin_row, end_row, begin_col, end_col;

	begin_row = end_row = Board::num_rows / 2;
	begin_col = end_col = Board::num_cols / 2;

	while (begin_row != -1 || end_row != Board::num_rows || begin_col != -1 || end_col != Board::num_cols)
	{
		for (int i = begin_row; i < end_row; i++)
		{
			for (int j = begin_col; j < end_col; i++)
			{
				sf::Vector2f v = { j*Board::cubicle_size.x,i*Board::cubicle_size.y + 50 };
				if (!board.ifInPArry(v) && !control.ifInAcArry(v))//is empty
				{
					m_object.setPosition(v);
					return;
				}
			}
		}
		if (begin_row > -1)
			begin_row--;
		if (begin_col > -1)
			begin_col--;
		if (end_row < Board::num_rows)
			end_row++;
		if (end_row < Board::num_cols)
			end_col++;
	}
}


int Player::getScore() const
{
	return m_score;
}

void Player::setScore(int score)
{
	m_score = score;
}

int Player::moving(Game&)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_lastPos = 4;
		return 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_lastPos = 0;
		return 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_lastPos = 1;
		return 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_lastPos = 2;
		return 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_lastPos = 3;
		return 3;
	}
	return (-1);
}

void Player::move(sf::Keyboard::Key d, Board & board, std::vector<std::shared_ptr<DynamicObject>> enemy, Game& game)
{
	sf::Vector2f old = { (float)m_boardPosition.x, (float)m_boardPosition.y };
	sf::Vector2i next;
	switch (d)
	{
	case sf::Keyboard::Left:
		next = { m_boardPosition.x - 1,m_boardPosition.y };
		break;
	case sf::Keyboard::Right:
		next = { m_boardPosition.x + 1,m_boardPosition.y };
		break;
	case sf::Keyboard::Up:
		next = { m_boardPosition.x ,m_boardPosition.y - 1 };
		break;
	case sf::Keyboard::Down:
		next = { m_boardPosition.x ,m_boardPosition.y + 1 };
		break;
	default:
		return;
	}
	if (next.x >= 0 && next.x < board.size().y && next.y >= 0 && next.y <board.size().x) {
		if (board.getModeSquare(m_boardPosition) == ICE && board.getModeSquare(next) == EMPTY)//begin close
			m_beginClose=next;
		else if (board.getModeSquare(m_boardPosition) == RUN && (board.getModeSquare(next) == ICE|| board.getModeSquare(next) == CLOSE)) {//end close
			m_endClose = m_boardPosition;
			board.close(m_beginClose, m_endClose,enemy);
		}
		setPosition(board.getPositionSquare(next));
		m_boardPosition = next;
		if (board.getModeSquare(next) == EMPTY)
			board.setSquare(m_boardPosition, RUN);
		

		auto passives = board.getP();
		for (auto& i : passives)
		{
			if (i->getPosition() == getPosition())
			{
				collide(i.get(), game, board, old);
				return;
			}
		}

		for (auto& dynamic : enemy)
		{
			if (dynamic->getPosition() == getPosition())
			{
				collide(dynamic.get(), game);
			}
		}
	}
}

void Player::cookieCrash(float value, Game& control)
{
	m_speed *= value;
	m_score += (2 * (Game::m_numLevel + 1));
	//ResourceManager::instance().getMusic("playMusic")->play();


}

void Player::setSpeed(float newSpeed)
{
	m_speed = newSpeed;
}

