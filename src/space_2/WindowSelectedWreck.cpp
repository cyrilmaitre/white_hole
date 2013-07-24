#include "WindowSelectedWreck.h"
#include "Game.h"


//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH			293
#define WINDOW_HEIGHT			120
#define TB_LABEL_LEVEL_X		200
#define LIFEBAR_OFFSETX			90
#define LIFEBAR_WIDTH			200
#define LIFEBAR_HEIGHT			14
#define BUTTON_WIDTH			80
#define BUTTON_HEIGHT			18
#define BUTTON_OFFSETX			10
#define BUTTON_OFFSETY			15


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelectedWreck::WindowSelectedWreck(Wreck* p_wreck)
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

	this->mTBShield.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBShield.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBShield.setText(Resource::resource->getBundle()->getString("uigShipSmallShieldLabel"));

	this->mTBArmor.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBArmor.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBArmor.setText(Resource::resource->getBundle()->getString("uigShipSmallArmorLabel"));

	this->mTBStructure.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBStructure.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBStructure.setText(Resource::resource->getBundle()->getString("uigShipSmallStructureLabel"));

	this->mButtonOpen.setWidth(BUTTON_WIDTH);
	this->mButtonOpen.setHeight(BUTTON_HEIGHT);
	this->mButtonOpen.setTitle(Resource::resource->getBundle()->getString("open"));

	this->mButtonRecycle.setWidth(BUTTON_WIDTH);
	this->mButtonRecycle.setHeight(BUTTON_HEIGHT);
	this->mButtonRecycle.setTitle(Resource::resource->getBundle()->getString("recycle"));
	this->mButtonRecycle.setEnable(false);

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);

	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));
	this->setWreck(p_wreck);
	this->notifyPositionChanged();
}

WindowSelectedWreck::~WindowSelectedWreck(void)
{
	for(int i = 0; i < LIFEBAR_COUNT; i++)
		if(this->mLifeBars[i] != NULL)
			delete this->mLifeBars[i];
}


//*************************************************************
// Getters - Setters
//*************************************************************
Wreck* WindowSelectedWreck::getWreck()
{
	return this->mWreck;
}

void WindowSelectedWreck::setWreck( Wreck* p_wreck )
{
	this->mWreck = p_wreck;
	this->notifyWreckChanged();
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelectedWreck::notifyPositionChanged()
{
	WindowSelected::notifyPositionChanged();
	this->updatePosition();
}

void WindowSelectedWreck::notifyWreckChanged()
{
	if(this->getWreck() != NULL)
	{
		this->setWindowTitle(Resource::resource->getBundle()->getString("uigObjectSelectedTitleWreck"));
		this->mTBNameValue.setText(this->getWreck()->getName());

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getWreck());

		Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(false);
	}
}

void WindowSelectedWreck::notifyOpenChanged()
{
	Window::notifyOpenChanged();
	if(Game::game->getUserInterface()->getWindowCargoLoot()->getWreck() == this->getWreck())
		Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(false);
}

void WindowSelectedWreck::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->getWreck() != NULL)
		{
			for(int i = 0; i < LIFEBAR_COUNT; i++)
				this->mLifeBars[i]->update();	

			if(Game::game->getMap()->getMapObjectSelector()->getObjectSelectedDistance() < WRECK_OPEN_DISTANCE)
			{
				this->mButtonOpen.setEnable(true);
			}
			else
			{
				this->mButtonOpen.setEnable(false);
				if(Game::game->getUserInterface()->getWindowCargoLoot()->getWreck() == this->getWreck())
					Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(false);
			}

			if(this->mButtonOpen.isClicked())
				this->openWreck();

			if(this->mButtonRecycle.isClicked())
				this->recycleWreck();
		}
	}
}

void WindowSelectedWreck::update( sf::Event p_event )
{
	this->mButtonOpen.update(p_event);
	this->mButtonRecycle.update(p_event);

	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);
	}
	WindowSelected::update(p_event);	
}

void WindowSelectedWreck::updatePosition()
{
	this->mTBName.setX(this->getContentX());
	this->mTBName.setY(this->getContentY());	

	this->mTBNameValue.setX(this->mTBName.getRightX() + TB_VALUE_OFFSETX);
	this->mTBNameValue.setY(this->getContentY());

	this->mTBShield.setX(this->getContentX());
	this->mTBShield.setY(this->mTBName.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBArmor.setX(this->getContentX());
	this->mTBArmor.setY(this->mTBShield.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBStructure.setX(this->getContentX());
	this->mTBStructure.setY(this->mTBArmor.getBottomY() + TB_LABEL_OFFSETY);	

	this->mButtonOpen.setX(this->getContentX());
	this->mButtonOpen.setY(this->mTBStructure.getBottomY() + BUTTON_OFFSETY);

	this->mButtonRecycle.setX(mButtonOpen.getRightX() + BUTTON_OFFSETX);
	this->mButtonRecycle.setY(this->mTBStructure.getBottomY() + BUTTON_OFFSETY);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShield.getY());
	this->mLifeBars[1]->setY(this->mTBArmor.getY());
	this->mLifeBars[2]->setY(this->mTBStructure.getY());
}

void WindowSelectedWreck::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mTBName.draw();
		this->mTBNameValue.draw();
		this->mTBShield.draw();
		this->mTBArmor.draw();
		this->mTBStructure.draw();
		this->mButtonOpen.draw();
		this->mButtonRecycle.draw();

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}

void WindowSelectedWreck::openWreck()
{
	if(this->getWreck() != NULL)
	{
		Game::game->getUserInterface()->getWindowCargoLoot()->setWreck(this->getWreck());
		Game::game->getUserInterface()->getWindowCargoLoot()->setOpen(true);
	}
}

void WindowSelectedWreck::recycleWreck()
{

}
