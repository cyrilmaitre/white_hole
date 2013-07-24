#include "SpriteParameter.h"
#include "Tools.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
SpriteParameter::SpriteParameter( sf::Texture* myImage )
{
	// Init with param
	this->mSprite.setTexture(*myImage);
}

SpriteParameter::SpriteParameter( sf::Texture* myImage, int p_spriteColumn, int p_spriteLine )
{
	// Init with param
	this->mTexture = myImage;
	this->mSprite.setTexture(*myImage);
	this->mSpriteColumn	= p_spriteColumn;
	this->mSpriteLine	= p_spriteLine;
	this->mSpriteWidth	= (int)(this->mSprite.getTexture()->getSize().x / this->mSpriteColumn);
	this->mSpriteHeight	= (int)(this->mSprite.getTexture()->getSize().y / this->mSpriteLine);
}

SpriteParameter::~SpriteParameter(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Sprite SpriteParameter::getSprite( std::string index )
{
	this->selectSprite(index);
	return this->mSprite;
}

sf::Sprite SpriteParameter::getSprite( int p_column, int p_line )
{
	this->selectSprite(p_column, p_line);
	return this->mSprite;
}

sf::Sprite SpriteParameter::getSpriteRandom()
{
	int column = Tools::random(0, this->getSpriteColumns() - 1);
	int line = Tools::random(0, this->getSpriteLines() - 1);
	return this->getSprite(column, line);
}

sf::Sprite SpriteParameter::getSpriteRandom( int newWidth, int newHeight )
{
	int column = Tools::random(0, this->getSpriteColumns() - 1);
	int line = Tools::random(0, this->getSpriteLines() - 1);
	sf::Sprite sprite = this->getSprite(column, line);

	// Scale
	float widthFactor = 1;
	float heightFactor = 1;
	if(newWidth > 0)
		widthFactor = (float)newWidth / (float)this->getSpriteWidth();
	if(newHeight > 0)
		heightFactor = (float)newHeight / (float)this->getSpriteHeight();
	sprite.setScale(widthFactor, heightFactor);

	return sprite;
}

int SpriteParameter::getSpriteLineRandom()
{
	return Tools::random(0, this->getSpriteLines() - 1);
}

int SpriteParameter::getSpriteColumnRandom()
{
	return Tools::random(0, this->getSpriteColumns() - 1);	
}

sf::Vector2i SpriteParameter::getSpriteIdRandom()
{
	sf::Vector2i returnValue;
	returnValue.x = this->getSpriteColumnRandom();
	returnValue.y = this->getSpriteLineRandom();
	return returnValue;
}

sf::Sprite& SpriteParameter::getSprite()
{
	return this->mSprite;
}

sf::Sprite* SpriteParameter::getSpritePtr( std::string index, int newWidth, int newHeight )
{
	sf::Sprite *sprite = new sf::Sprite();
	sprite->setTexture(*this->mTexture);
	this->selectSprite(index, sprite);

	// Scale
	float widthFactor = 1;
	float heightFactor = 1;
	if(newWidth > 0)
		widthFactor = (float)newWidth / (float)this->getSpriteWidth();
	if(newHeight > 0)
		heightFactor = (float)newHeight / (float)this->getSpriteHeight();
	sprite->setScale(widthFactor, heightFactor);

	return sprite;
}

sf::Sprite* SpriteParameter::getSpritePtr( int p_column, int p_line, int newWidth, int newHeight )
{
	sf::Sprite *sprite = new sf::Sprite();
	sprite->setTexture(*this->mTexture);
	this->selectSprite(p_column, p_line, sprite);

	// Scale
	float widthFactor = 1;
	float heightFactor = 1;
	if(newWidth > 0)
		widthFactor = (float)newWidth / (float)this->getSpriteWidth();
	if(newHeight > 0)
		heightFactor = (float)newHeight / (float)this->getSpriteHeight();
	sprite->setScale(widthFactor, heightFactor);

	return sprite;
}

sf::Texture* SpriteParameter::getTexture( std::string index )
{
	this->selectSprite(index);

	sf::Texture *texture = new sf::Texture();
	texture->loadFromImage(this->mSprite.getTexture()->copyToImage(), this->mSprite.getTextureRect());
	return texture;
}

sf::Texture* SpriteParameter::getTexture( int p_column, int p_line )
{
	this->selectSprite(p_column, p_line);

	sf::Texture *texture = new sf::Texture();
	texture->loadFromImage(this->mSprite.getTexture()->copyToImage(), this->mSprite.getTextureRect());
	return texture;
}

sf::Texture* SpriteParameter::getTexture()
{
	sf::Texture *texture = new sf::Texture();
	texture->loadFromImage(this->mSprite.getTexture()->copyToImage(), this->mSprite.getTextureRect());
	return texture;
}

int SpriteParameter::getSpriteColumns()
{
	return this->mSpriteColumn;
}

int SpriteParameter::getSpriteLines()
{
	return this->mSpriteLine;
}

int SpriteParameter::getSpriteWidth()
{
	return this->mSpriteWidth;
}

int SpriteParameter::getSpriteHeight()
{
	return this->mSpriteHeight;
}


//*************************************************************
// Methodes
//*************************************************************
void SpriteParameter::selectSprite( std::string index )
{
	int delimeterIndex = index.find_first_of("-");
	int column = 0;
	int line = 0;

	if(delimeterIndex != std::string::npos)
	{
		column	= Tools::getIntFromString(index.substr(0, delimeterIndex));
		line	= Tools::getIntFromString(index.substr(delimeterIndex+1, index.length()));
		this->selectSprite(column, line);
	}
}

void SpriteParameter::selectSprite( std::string index, sf::Sprite *sprite )
{
	int delimeterIndex = index.find_first_of("-");
	int column = 0;
	int line = 0;

	if(delimeterIndex != std::string::npos)
	{
		column	= Tools::getIntFromString(index.substr(0, delimeterIndex));
		line	= Tools::getIntFromString(index.substr(delimeterIndex+1, index.length()));
		this->selectSprite(column, line, sprite);
	}
}

void SpriteParameter::selectSprite( int p_column, int p_line )
{
	// Check param
	if(p_column < 0)
		p_column = 0;
	else if(p_column >= this->mSpriteColumn)
		p_column = this->mSpriteColumn - 1;

	if(p_line < 0)
		p_line = 0;
	else if(p_line >= this->mSpriteLine)
		p_line = this->mSpriteLine - 1;

	this->mSprite.setTextureRect(sf::IntRect(	p_column * this->mSpriteWidth, 
												p_line * this->mSpriteHeight, 
												this->mSpriteWidth, 
												this->mSpriteHeight));
}

void SpriteParameter::selectSprite( int p_column, int p_line, sf::Sprite *sprite )
{
	// Check param
	if(p_column < 0)
		p_column = 0;
	else if(p_column >= this->mSpriteColumn)
		p_column = this->mSpriteColumn - 1;

	if(p_line < 0)
		p_line = 0;
	else if(p_line >= this->mSpriteLine)
		p_line = this->mSpriteLine - 1;

	sprite->setTextureRect(sf::IntRect(	p_column * this->mSpriteWidth, 
										p_line * this->mSpriteHeight, 
										this->mSpriteWidth, 
										this->mSpriteHeight));
}

void SpriteParameter::resizeSprite( int newWidth, int newHeight )
{
	float widthFactor = 1;
	float heightFactor = 1;
	if(newWidth > 0)
		widthFactor = (float)newWidth / (float)this->getSpriteWidth();
	if(newHeight > 0)
		heightFactor = (float)newHeight / (float)this->getSpriteHeight();
	this->mSprite.setScale(widthFactor, heightFactor);
}


