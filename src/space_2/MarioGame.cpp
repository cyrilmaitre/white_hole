#include "MarioGame.h"
#include "MarioGameBlock.h"
#include "MarioGameGround.h"
#include "MarioGameMario.h"
#include "MarioGameBrick.h"


//*************************************************************
// Define
//*************************************************************
#define GAME_HEIGHT			256
#define METERTOPIXEL		32
#define PIXELTOMETER		1 / METERTOPIXEL


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGame::MarioGame(void)
{
	this->mWorldBlocks = NULL;
	this->mBodyGround = NULL;

	b2Vec2 gravity(0.0f, -1.0f);
	this->mWorld = new b2World(gravity);
	this->mWorld->SetContactListener(this);
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

MarioGameBlock* MarioGame::getBlock( int p_x, int p_y )
{
	if(p_x < 0 || p_x >= this->mWorldBlocksSize.x || p_y < 0 || p_y >= this->mWorldBlocksSize.y)
		return NULL;

	return this->mWorldBlocks[p_x][p_y];
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
	//*********************************************
	// Destroy
	//*********************************************
	this->destroyWorldBlocks();
	if(this->mBodyGround != NULL)
	{
		this->mWorld->DestroyBody(this->mBodyGround);
		this->mBodyGround = NULL;
	}

	//*********************************************
	// Init
	//*********************************************
	this->mWorldBlocksSize.x = ceil(Resource::resource->getViewUi()->getSize().x / MARIOGAME_BLOCK_WIDTH);
	this->mWorldBlocksSize.y = ceil(GAME_HEIGHT / MARIOGAME_BLOCK_HEIGHT);
	this->mWorldBlocks = new MarioGameBlock**[this->mWorldBlocksSize.x];
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i] = new MarioGameBlock*[this->mWorldBlocksSize.y];
		for(int j = 0; j < this->mWorldBlocksSize.y; j++)
		{
			this->mWorldBlocks[i][j] = NULL;
		}
	}

	//*********************************************
	// Create ground
	//*********************************************
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i][0] = new MarioGameGround(this, sf::Vector2i(i, 0));
	}
	this->updatePosition();

	b2Vec2 vs[4];
	vs[0].Set(0.0f, 10.0f);
	vs[1].Set(0.0f, 1.0f);
	vs[2].Set(MarioGame::pixelToMeter(Resource::resource->getViewUi()->getSize().x), 1.0f);
	vs[3].Set(MarioGame::pixelToMeter(Resource::resource->getViewUi()->getSize().x), 10.0f);
	b2ChainShape chain;
	chain.CreateChain(vs, 4);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	this->mBodyGround = this->mWorld->CreateBody(&groundBodyDef);
	this->mBodyGround->CreateFixture(&chain, 0.0f);


	for(int i = 5; i < 20; i++)
		this->mWorldBlocks[i][3] = new MarioGameBrick(this, sf::Vector2i(i,3));

	for(int i = 15; i < 20; i++)
		this->mWorldBlocks[i][4] = new MarioGameBrick(this, sf::Vector2i(i,4));
}

void MarioGame::updatePosition()
{
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i][0]->setPosition(	this->getX() + i * MARIOGAME_BLOCK_WIDTH + MARIOGAME_BLOCK_WIDTH / 2, 
												this->getBottomY() - MARIOGAME_BLOCK_HEIGHT / 2);
	}
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

float MarioGame::pixelToMeter( float p_pixel )
{
	return p_pixel * PIXELTOMETER;
}

sf::Vector2f MarioGame::pixelToMeter( sf::Vector2f p_pixel )
{
	sf::Vector2f meter;
	meter.x = p_pixel.x * PIXELTOMETER;
	meter.y = p_pixel.y * PIXELTOMETER;
	return meter;
}

float MarioGame::meterToPixel( float p_meter )
{
	return p_meter * METERTOPIXEL;
}

sf::Vector2f MarioGame::meterToPixel( sf::Vector2f p_meter )
{
	sf::Vector2f pixel;
	pixel.x = p_meter.x * METERTOPIXEL;
	pixel.y = p_meter.y * METERTOPIXEL;
	return pixel;
}

void MarioGame::BeginContact( b2Contact* contact )
{
	MarioGameUserData* data = NULL;

	b2Fixture* a = contact->GetFixtureA();
	if(a->GetBody()->GetUserData() != NULL)
	{
		data = (MarioGameUserData*)a->GetBody()->GetUserData();
		data->BeginContact(contact, MarioGameUserData::UserDataIndex::IndexA);
	}

	b2Fixture* b = contact->GetFixtureB();
	if(b->GetBody()->GetUserData() != NULL)
	{
		data = (MarioGameUserData*)b->GetBody()->GetUserData();
		data->BeginContact(contact, MarioGameUserData::UserDataIndex::IndexB);
	}
}

void MarioGame::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{
	MarioGameUserData* data = NULL;

	b2Fixture* a = contact->GetFixtureA();
	if(a->GetBody()->GetUserData() != NULL)
	{
		data = (MarioGameUserData*)a->GetBody()->GetUserData();
		data->PreSolve(contact, oldManifold, MarioGameUserData::UserDataIndex::IndexA);
	}

	b2Fixture* b = contact->GetFixtureB();
	if(b->GetBody()->GetUserData() != NULL)
	{
		data = (MarioGameUserData*)b->GetBody()->GetUserData();
		data->PreSolve(contact, oldManifold, MarioGameUserData::UserDataIndex::IndexB);
	}
}
