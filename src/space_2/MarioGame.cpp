#include "MarioGame.h"
#include "MarioGameBlock.h"
#include "MarioGameGround.h"
#include "MarioGameMario.h"
#include "MarioGameBrick.h"
#include "MarioGameBonus.h"
#include "MarioGameCoin.h"


//*************************************************************
// Define
//*************************************************************
#define GAME_HEIGHT						384
#define METERTOPIXEL					32
#define PIXELTOMETER					1 / METERTOPIXEL
#define GEN_BRICKTICK					25.0f		// percent
#define GEN_BRICKSSIZE_MIN				2			// blocks
#define GEN_BRICKSSIZE_MAX				10			// blocks
#define GEN_BONUSTICK					5.0f		// percent
#define GEN_COINTICK					10.0f		// percent		
#define GEN_COINTICKDOUBLE				50.0f		// percent
#define GEN_COINSIZE_MIN				2			// coins
#define GEN_COINSIZE_MAX				8			// coins
#define KEYPADSPRITE_MARGINLEFT			20
#define KEYPADTB_MARGINLEFT				10
#define CREDITLABEL_MARGINTOP			10
#define CREDITLABEL_MARGINRIGHT			5
#define TB_KEYPAD_FONTSIZE				20
#define TB_CREDIT_FONTSIZE				18


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarioGame::MarioGame(void)
{
	this->mWorldBlocks = NULL;
	this->mBodyGround = NULL;

	b2Vec2 gravity(0.0f, -75.0f);
	this->mWorld = new b2World(gravity);
	this->mWorld->SetContactListener(this);
	this->mMario = new MarioGameMario(this);
	this->mWorldTimeStep = 1.0f / 60.0f;
	this->mWorldVelocityIter = 6;
	this->mWorldPositionIter = 2;

	this->setSize(Resource::resource->getViewUi()->getSize().x, GAME_HEIGHT);
	this->mSpriteKeyPad.setTexture(*Resource::resource->getTexture(IMG_MARIOGAME_KEYPAD));
	this->mTBKeyPad.setText(Resource::resource->getBundle()->getString("marioKeypadToMove"));
	this->mTBKeyPad.setFontSize(TB_KEYPAD_FONTSIZE);
	this->mTBCreditLabel.setText(Resource::resource->getBundle()->getString("marioCredit"));
	this->mTBCreditLabel.setFontSize(TB_CREDIT_FONTSIZE);
	this->mTBCredit.setFontSize(TB_CREDIT_FONTSIZE);
	this->mCredit = 0.0f;
	this->notifyCreditChanged();
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

double MarioGame::getCredit()
{
	return this->mCredit;
}

void MarioGame::setCredit( double p_credit )
{
	if(this->mCredit != p_credit)
	{
		this->mCredit = p_credit;
		this->notifyCreditChanged();
	}
}

void MarioGame::incCredit( double p_credit )
{
	this->setCredit(this->mCredit + p_credit);
}


//*************************************************************
// Methods
//*************************************************************
void MarioGame::reset()
{
	this->setCredit(0.0);
	this->createWorld();
}

void MarioGame::createWorld()
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
	vs[0].Set(0.0f, 50.0f);
	vs[1].Set(0.0f, 1.0f);
	vs[2].Set(MarioGame::pixelToMeter(Resource::resource->getViewUi()->getSize().x), 1.0f);
	vs[3].Set(MarioGame::pixelToMeter(Resource::resource->getViewUi()->getSize().x), 50.0f);
	b2ChainShape chain;
	chain.CreateChain(vs, 4);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	this->mBodyGround = this->mWorld->CreateBody(&groundBodyDef);
	this->mBodyGround->CreateFixture(&chain, 0.0f);


	//*********************************************
	// Generate new world
	//*********************************************
	this->createBricks();
	this->createCoins();


	//*********************************************
	// Reset mario
	//*********************************************
	this->mMario->resetPosition();
}

void MarioGame::update( sf::Event p_event )
{
	Object::update(p_event);
	this->mMario->update(p_event);
}

void MarioGame::update()
{
	// Update framerate
	this->updateFrameRate();

	// Update world
	this->mWorldTimeStep = 1 / this->mFrameRate;
	this->mWorld->Step(this->mWorldTimeStep, this->mWorldVelocityIter, this->mWorldPositionIter);
	// Update mario
	this->mMario->update();
	// Update blocks
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		for(int j = 0; j < this->mWorldBlocksSize.y; j++)
		{
			if(this->mWorldBlocks[i][j] != NULL)
			{
				// Check if coin
				MarioGameCoin* coin = dynamic_cast<MarioGameCoin*>(this->mWorldBlocks[i][j]);
				if(coin != NULL && coin->getCoinState() == MarioGameCoin::CoinState::Destroy)
				{
					delete this->mWorldBlocks[i][j];
					this->mWorldBlocks[i][j] = NULL;
				}
				else
				{
					this->mWorldBlocks[i][j]->update();
				}
			}
		}
	}

	
}

void MarioGame::updateFrameRate()
{	
	this->mFrameRate = 1.0f / this->mGameClock.getElapsedTimeAsSeconds();
	this->mGameClock.restart();
}

void MarioGame::updatePosition()
{
	this->mSpriteKeyPad.setPosition(this->getX() + KEYPADSPRITE_MARGINLEFT, this->getY());
	this->mTBKeyPad.setPosition(this->mSpriteKeyPad.getPosition().x + this->mSpriteKeyPad.getGlobalBounds().width + KEYPADTB_MARGINLEFT, this->mSpriteKeyPad.getPosition().y + (this->mSpriteKeyPad.getGlobalBounds().height - this->mTBKeyPad.getHeight()) / 2);
	this->mTBCreditLabel.setPosition(this->mSpriteKeyPad.getPosition().x, this->mSpriteKeyPad.getPosition().y + this->mSpriteKeyPad.getGlobalBounds().height + CREDITLABEL_MARGINTOP);
	this->mTBCredit.setPosition(this->mTBCreditLabel.getRightX() + CREDITLABEL_MARGINRIGHT, this->mTBCreditLabel.getY());
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		this->mWorldBlocks[i][0]->setPosition(	this->getX() + i * MARIOGAME_BLOCK_WIDTH + MARIOGAME_BLOCK_WIDTH / 2, 
												this->getBottomY() - MARIOGAME_BLOCK_HEIGHT / 2);
	}
}

void MarioGame::draw()
{
	// Draw ui
	Resource::resource->getApp()->draw(this->mSpriteKeyPad);
	this->mTBKeyPad.draw();
	this->mTBCreditLabel.draw();
	this->mTBCredit.draw();

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
	this->createWorld();
}

void MarioGame::notifyCreditChanged()
{
	this->mTBCredit.setText(Tools::formatNumber((long)this->mCredit) + " " + Resource::resource->getBundle()->getString("creditAb"));
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

void MarioGame::createBricks()
{
	this->createBricks(3);
	this->createBricks(6);
}

void MarioGame::createBricks( int p_line )
{
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		if(this->mWorldBlocks[i][p_line] == NULL)
		{
			float gen = Tools::random(0.0f, 100.0f);
			if(this->getBlock(i - 1, p_line) == NULL && this->getBlock(i - 2, p_line) != NULL)
				gen = 100.0f;
			if(gen < GEN_BRICKTICK)
			{
				int size = Tools::random(GEN_BRICKSSIZE_MIN, GEN_BRICKSSIZE_MAX);
				if(i + size >= this->mWorldBlocksSize.x)
					size = this->mWorldBlocksSize.x - 1 - i;
				for(int j = i; j <= i + size; j++)
				{
					float genBonus = Tools::random(0.0f, 100.0f);
					if(genBonus < GEN_BONUSTICK)
						this->mWorldBlocks[j][p_line] = new MarioGameBonus(this, sf::Vector2i(j, p_line));
					else
						this->mWorldBlocks[j][p_line] = new MarioGameBrick(this, sf::Vector2i(j, p_line));
				}
			}
		}
	}
}

void MarioGame::createCoins()
{
	this->createCoins(1);
	this->createCoins(4);
	this->createCoins(7);
}

void MarioGame::createCoins( int p_line )
{
	for(int i = 0; i < this->mWorldBlocksSize.x; i++)
	{
		if(this->mWorldBlocks[i][p_line] == NULL)
		{
			float gen = Tools::random(0.0f, 100.0f);
			bool genDouble = Tools::random(0.0f, 100.0f) < GEN_COINTICKDOUBLE;
			if(gen < GEN_COINTICK)
			{
				int size = Tools::random(GEN_COINSIZE_MIN, GEN_COINSIZE_MAX);
				if(i + size >= this->mWorldBlocksSize.x)
					size = this->mWorldBlocksSize.x - 1 - i;
				for(int j = i; j <= i + size; j++)
				{
					this->mWorldBlocks[j][p_line] = new MarioGameCoin(this, sf::Vector2i(j, p_line));
					if(genDouble)
						this->mWorldBlocks[j][p_line + 1] = new MarioGameCoin(this, sf::Vector2i(j, p_line + 1));
				}
			}
		}
	}
}

