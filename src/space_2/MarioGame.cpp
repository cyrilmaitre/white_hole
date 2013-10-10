#include "MarioGame.h"
#include "MarioGameBlock.h"
#include "MarioGameGround.h"
#include "MarioGameMario.h"


//*************************************************************
// Define
//*************************************************************
#define GAME_HEIGHT		256


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGame::MarioGame(void)
{
	this->mWorldBlocks = NULL;

	b2Vec2 gravity(0.0f, -10.0f);
	this->mWorld = new b2World(gravity);
	this->mMario = new MarioGameMario(this);
	this->mWorldTimeStep = 1.0f / 60.0f;
	this->mWorldVelocityIter = 6;
	this->mWorldPositionIter = 2;

	this->setSize(Resource::resource->getViewUi()->getSize().x, GAME_HEIGHT);
}

MarioGame::~MarioGame(void)
{
	this->destroyWorldBlocks();
	delete this->mWorld;
}

void MarioGame::destroyWorldBlocks()
{
	if(this->mWorldBlocks != NULL)
	{
		for(int i = 0; i < this->mWorldBlocksSize.x; i++)
		{
			if(this->mWorldBlocks[i] != NULL)
			{
				for(int j = 0; j < this->mWorldBlocksSize.y; j++)
				{
					if(this->mWorldBlocks[i][j] != NULL)
						delete this->mWorldBlocks[i][j];
				}
				delete this->mWorldBlocks[i];
			}
		}
	}
}


//*************************************************************
// Getters - Setters
//*************************************************************
b2World* MarioGame::getWorld()
{
	return this->mWorld;
}


//*************************************************************
// Methods
//*************************************************************
void MarioGame::update( sf::Event p_event )
{
	Object::update(p_event);
	this->mMario->update(p_event);
}

void MarioGame::update()
{
	// Update world
	this->mWorld->Step(this->mWorldTimeStep, this->mWorldVelocityIter, this->mWorldPositionIter);

	// Update blocks
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		for(int j = 0; j < this->mWorldBlocksSize.y; j++)
		{
			if(this->mWorldBlocks[i][j] != NULL)
				this->mWorldBlocks[i][j]->update();
		}
	}

	// Update mario
	this->mMario->update();
}

void MarioGame::createWorldBlocks()
{
	this->destroyWorldBlocks();
	this->mWorldBlocksSize.x = ceil(Resource::resource->getViewUi()->getSize().x / MARIOGAME_BLOCK_WIDTH);
	this->mWorldBlocksSize.y = ceil(GAME_HEIGHT / MARIOGAME_BLOCK_HEIGHT);

	// Init
	this->mWorldBlocks = new MarioGameBlock**[this->mWorldBlocksSize.x];
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i] = new MarioGameBlock*[this->mWorldBlocksSize.y];
		for(int j = 0; j < this->mWorldBlocksSize.y; j++)
		{
			this->mWorldBlocks[i][j] = NULL;
		}
	}

	// Create ground
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i][0] = new MarioGameGround(this, sf::Vector2i(i, 0));
	}
}

void MarioGame::updatePosition()
{

}

void MarioGame::draw()
{
	// Draw blocks
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		for(int j = 0; j < this->mWorldBlocksSize.y; j++)
		{
			if(this->mWorldBlocks[i][j] != NULL)
				this->mWorldBlocks[i][j]->draw();
		}
	}

	// Draw mario
	this->mMario->draw();
}

void MarioGame::notifyPositionChanged()
{
	Object::notifyPositionChanged();
	this->updatePosition();
}

void MarioGame::notifySizeChanged()
{
	Object::notifySizeChanged();
	this->createWorldBlocks();
}
