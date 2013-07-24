#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class SpriteParameter
{
public:
	// Constructor - Destructor
	SpriteParameter(sf::Texture* myImage);
	SpriteParameter(sf::Texture* myImage, int p_spriteColumn, int p_spriteLine);
	~SpriteParameter(void);

	// Getters - Setters
	sf::Sprite getSprite(std::string index);
	sf::Sprite getSprite(int p_column, int p_line);
	sf::Sprite getSpriteRandom();
	sf::Sprite getSpriteRandom(int newWidth, int newHeight);
	int getSpriteLineRandom();
	int getSpriteColumnRandom();
	sf::Vector2i getSpriteIdRandom();
	sf::Sprite& getSprite();
	sf::Sprite* getSpritePtr(std::string index, int newWidth = 0, int newHeight = 0);
	sf::Sprite* getSpritePtr(int p_column, int p_line, int newWidth = 0, int newHeight = 0);
	sf::Texture* getTexture(std::string index);
	sf::Texture* getTexture(int p_column, int p_line);
	sf::Texture* getTexture();

	int getSpriteColumns();
	int getSpriteLines();
	int getSpriteWidth();
	int getSpriteHeight();

	// Methods
	void selectSprite(std::string index);
	void selectSprite(std::string index, sf::Sprite *sprite);
	void selectSprite(int p_column, int p_line);
	void selectSprite(int p_column, int p_line, sf::Sprite *sprite);
	void resizeSprite(int newWidth, int newHeight);


private:
	// Attributs
	sf::Texture *mTexture;
	sf::Sprite mSprite;

	int mSpriteColumn;
	int mSpriteLine;
	int mSpriteWidth;
	int mSpriteHeight;
};
