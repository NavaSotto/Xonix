#include "ResourceManager.h"


//---------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
}
//---------------------------------------------------------------------

ResourceManager & ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}


const sf::Texture & ResourceManager::getPicture(std::string picture)
{
	return m_texture.at(picture);
}



const std::unique_ptr<sf::Music> & ResourceManager::getMusic(std::string sound)
{
	//return m_music->at(sound);
	return m_music.at(sound);
}



const sf::Font & ResourceManager::getText(std::string font)
{
	return m_text.at(font);
}
//---------------------------------------------------------------------
sf::Texture  ResourceManager::createTexture(const std::string& picture)
{
	sf::Texture texture;
	texture.loadFromFile(picture);
	return texture;

}



std::unique_ptr<sf::Music> ResourceManager::createMusic(const std::string & sound)
{
	auto music = std::make_unique<sf::Music>();
	music->openFromFile(sound);
	return music;
}

sf::Font ResourceManager::createText(const std::string & font)
{
	sf::Font text;
	text.loadFromFile(font);
	return text;
}


//---------------------------------------------------------------------
ResourceManager::ResourceManager()
{
	
	m_texture.insert(std::make_pair("winnerScreen", createTexture("winnerScreen.png")));
	m_texture.insert(std::make_pair("openScreen", createTexture("openScreen.png")));
	m_texture.insert(std::make_pair("gameOver", createTexture("gameOver.png")));
	m_texture.insert(std::make_pair("menuScreen", createTexture("menuScreen.png")));
	m_texture.insert(std::make_pair("helpScreen", createTexture("helpScreen.png")));

	m_texture.insert(std::make_pair("levelScreen", createTexture("levelScreen.png")));
	m_texture.insert(std::make_pair("gameOver", createTexture("gameOver.png")));
	m_texture.insert(std::make_pair("player", createTexture("player.png")));
	
	m_texture.insert(std::make_pair("normalEnemy", createTexture("normalEnemy.png")));

	m_texture.insert(std::make_pair("specialEnemy", createTexture("specialEnemy.png")));

	m_texture.insert(std::make_pair("increaseScore", createTexture("increaseScore.png")));

	m_texture.insert(std::make_pair("increaseLives", createTexture("increaseLives.png")));
	m_texture.insert(std::make_pair("increaseSpeed", createTexture("increaseSpeed.png")));
	m_texture.insert(std::make_pair("emptySquare", createTexture("emptySquare.png")));
	m_texture.insert(std::make_pair("closeSquare", createTexture("closeSquare.png")));
	m_texture.insert(std::make_pair("runSquare", createTexture("runSquare.png")));


	m_texture.insert(std::make_pair("ice", createTexture("ice.png")));

	m_music.emplace("gameMusic", std::unique_ptr<sf::Music>(createMusic("gameMusic.ogg")));
	m_music.emplace("playMusic", std::unique_ptr<sf::Music>(createMusic("playMusic.ogg")));

	m_text.insert(std::make_pair("Toledo", createText("Toledo__.ttf")));
	


}
//---------------------------------------------------------------------
ResourceManager::ResourceManager(const ResourceManager &other)
{
}

