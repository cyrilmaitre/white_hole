#include "BackgroundSpace.h"
#include "SpriteParameterFactory.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDSPACE_MAX_CACHED		24


//*************************************************************
// Statics
//*************************************************************
std::vector<BackgroundSpace*> BackgroundSpace::mBackgroundSpaceCached;
IdGenerator BackgroundSpace::mIdGenerator;


//*************************************************************
// Constructor - Destructor
//*************************************************************
BackgroundSpace::BackgroundSpace(int p_width, int p_height, int p_columnsCount, int p_linesCount)
{
	this->mId = BackgroundSpace::mIdGenerator.getNextId();
	this->mWidth = p_width;
	this->mHeight = p_height;
	this->mColumnsCount = p_columnsCount;
	this->mLinesCount = p_linesCount;
	this->mBackgroundTexture = NULL;

	this->mBackgroundTiles = new int*[this->mColumnsCount];
	for(int i = 0; i < this->mColumnsCount; i++)
	{
		this->mBackgroundTiles[i] = new int[this->mLinesCount];
	}
}

BackgroundSpace::~BackgroundSpace(void)
{
	this->uncacheBackgroundSpace(this);

	for(int i = 0; i < this->mColumnsCount; i++)
	{
		delete this->mBackgroundTiles[i];
	}
	delete this->mBackgroundTiles;

	if(this->mBackgroundTexture != NULL)
		delete this->mBackgroundTexture;
}


//*************************************************************
// Getters - Setters
//*************************************************************
int BackgroundSpace::getId()
{
	return this->mId;
}

int BackgroundSpace::getBackgroundTile( int p_column, int p_line )
{
	return this->mBackgroundTiles[p_column][p_line];
}

void BackgroundSpace::setBackgroundTile( int p_item_id, int p_column, int p_line )
{
	this->mBackgroundTiles[p_column][p_line] = p_item_id;
}

bool BackgroundSpace::hasBackgroundTexture()
{
	return this->mBackgroundTexture != NULL;
}

sf::RenderTexture* BackgroundSpace::getBackgroundTexture()
{
	if(!this->hasBackgroundTexture())
		this->generateBackgroundTexture();

	return this->mBackgroundTexture;
}

int BackgroundSpace::getColumnsCount()
{
	return this->mColumnsCount;
}

int BackgroundSpace::getLinesCount()
{
	return this->mLinesCount;
}

int BackgroundSpace::getBackgroundSpaceCachedCount()
{
	return BackgroundSpace::mBackgroundSpaceCached.size();
}


//*************************************************************
// Methodes
//*************************************************************
void BackgroundSpace::generateBackgroundTexture()
{
	// Generate
	this->mBackgroundTexture = new sf::RenderTexture();
	this->mBackgroundTexture->create(this->mWidth, this->mHeight);
	SpriteParameter *spriteParameter = SpriteParameterFactory::getSpriteParameterSpaceBackground();

	// Draw Background
	for(int i = 0; i < this->mColumnsCount; i++)
	{
		for(int j = 0; j < this->mLinesCount; j++)
		{
			sf::Sprite tmpSprite = spriteParameter->getSprite(	this->mBackgroundTiles[i][j] % spriteParameter->getSpriteColumns(), 
																this->mBackgroundTiles[i][j] / spriteParameter->getSpriteColumns());
			tmpSprite.setPosition(i * spriteParameter->getSpriteWidth(), j * spriteParameter->getSpriteHeight());
			this->mBackgroundTexture->draw(tmpSprite);
		}
	}

	// Save
	this->mBackgroundTexture->display();
	BackgroundSpace::cacheBackgroundSpace(this);
}

void BackgroundSpace::cacheBackgroundSpace( BackgroundSpace *p_backgroundSpace )
{
	if(p_backgroundSpace == NULL)
		return;

	if(BackgroundSpace::mBackgroundSpaceCached.size() >= BACKGROUNDSPACE_MAX_CACHED)
		BackgroundSpace::uncacheBackgroundSpace(0); // Remove first

	BackgroundSpace::mBackgroundSpaceCached.push_back(p_backgroundSpace);
}

void BackgroundSpace::uncacheBackgroundSpace( BackgroundSpace *p_backgroundTexture )
{
	if(p_backgroundTexture == NULL)
		return;

	for(int i = 0; i < BackgroundSpace::mBackgroundSpaceCached.size(); i++)
	{
		if(BackgroundSpace::mBackgroundSpaceCached[i] != NULL && BackgroundSpace::mBackgroundSpaceCached[i]->getId() == p_backgroundTexture->getId())
		{
			BackgroundSpace::uncacheBackgroundSpace(i);
			return;
		}
	}
}

void BackgroundSpace::uncacheBackgroundSpace( int p_index )
{
	delete BackgroundSpace::mBackgroundSpaceCached[p_index]->mBackgroundTexture;
	BackgroundSpace::mBackgroundSpaceCached[p_index]->mBackgroundTexture = NULL;

	BackgroundSpace::mBackgroundSpaceCached.erase(BackgroundSpace::mBackgroundSpaceCached.begin() + p_index);
}
