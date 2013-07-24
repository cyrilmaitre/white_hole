#include "WindowSelectedCharacterShip.h"
#include "Game.h"

//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH			293
#define WINDOW_HEIGHT			88
#define TB_LABEL_LEVEL_X		200
#define LIFEBAR_OFFSETX			90
#define LIFEBAR_WIDTH			200
#define LIFEBAR_HEIGHT			14


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelectedCharacterShip::WindowSelectedCharacterShip( CharacterShip* p_ship )
{
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i] = NULL;

	this->mTBName.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBName.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBName.setText(Resource::resource->getBundle()->getString("uigObjectSelectedObjectNameLabel"));

	this->mTBNameValue.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBNameValue.setFontSize(TB_LABEL_FONTSIZE);

	this->mTBLevel.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBLevel.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBLevel.setText(Resource::resource->getBundle()->getString("uigObjectSelectedObjectLevelLabel"));

	this->mTBLevelValue.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBLevelValue.setFontSize(TB_LABEL_FONTSIZE);

	this->mTBShield.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBShield.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBShield.setText(Resource::resource->getBundle()->getString("uigShipSmallShieldLabel"));

	this->mTBArmor.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBArmor.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBArmor.setText(Resource::resource->getBundle()->getString("uigShipSmallArmorLabel"));

	this->mTBStructure.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBStructure.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBStructure.setText(Resource::resource->getBundle()->getString("uigShipSmallStructureLabel"));

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);

	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));
	this->setCharacterShip(p_ship);
	this->notifyPositionChanged();
}

WindowSelectedCharacterShip::~WindowSelectedCharacterShip(void)
{
	for(int i = 0; i < LIFEBAR_COUNT; i++)
		if(this->mLifeBars[i] != NULL)
			delete this->mLifeBars[i];
}


//*************************************************************
// Getters - Setters
//*************************************************************
CharacterShip* WindowSelectedCharacterShip::getCharacterShip()
{
	return this->mCharacterShip;
}

void WindowSelectedCharacterShip::setCharacterShip( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
	this->notifyCharacterShipChanged();
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelectedCharacterShip::notifyPositionChanged()
{
	WindowSelected::notifyPositionChanged();
	this->updatePosition();
}

void WindowSelectedCharacterShip::notifyCharacterShipChanged()
{
	if(this->getCharacterShip() != NULL)
	{
		this->setWindowTitle(Resource::resource->getBundle()->getString("uigObjectSelectedTitleCharacterShip") + " - " + Game::game->getCharacter()->getName());
		this->mTBNameValue.setText(this->getCharacterShip()->getShipModel()->getName());
		this->mTBLevelValue.setText(Tools::buildStringWithInt(this->getCharacterShip()->getLevel()));

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getCharacterShip());
	}
}

void WindowSelectedCharacterShip::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->getCharacterShip() != NULL)
		{
			for(int i = 0; i < LIFEBAR_COUNT; i++)
				this->mLifeBars[i]->update();		
		}
	}
}

void WindowSelectedCharacterShip::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);
	}
	WindowSelected::update(p_event);
}

void WindowSelectedCharacterShip::updatePosition()
{
	this->mTBName.setX(this->getContentX());
	this->mTBName.setY(this->getContentY());	

	this->mTBNameValue.setX(this->mTBName.getRightX() + TB_VALUE_OFFSETX);
	this->mTBNameValue.setY(this->getContentY());

	this->mTBLevel.setX(this->getContentX() + TB_LABEL_LEVEL_X);
	this->mTBLevel.setY(this->getContentY());

	this->mTBLevelValue.setX(this->mTBLevel.getRightX() + TB_VALUE_OFFSETX);
	this->mTBLevelValue.setY(this->getContentY());

	this->mTBShield.setX(this->getContentX());
	this->mTBShield.setY(this->mTBName.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBArmor.setX(this->getContentX());
	this->mTBArmor.setY(this->mTBShield.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBStructure.setX(this->getContentX());
	this->mTBStructure.setY(this->mTBArmor.getBottomY() + TB_LABEL_OFFSETY);	

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShield.getY());
	this->mLifeBars[1]->setY(this->mTBArmor.getY());
	this->mLifeBars[2]->setY(this->mTBStructure.getY());
}

void WindowSelectedCharacterShip::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mTBName.draw();
		this->mTBNameValue.draw();
		this->mTBLevel.draw();
		this->mTBLevelValue.draw();
		this->mTBShield.draw();
		this->mTBArmor.draw();
		this->mTBStructure.draw();

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}
