#include "WindowSelectedStation.h"
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
#define STATION_DOCK_DISTANCE	250


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelectedStation::WindowSelectedStation( Station* p_station )
{
	this->mStation = NULL;
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

	this->mButtoDock.setWidth(BUTTON_WIDTH);
	this->mButtoDock.setHeight(BUTTON_HEIGHT);
	this->mButtoDock.setTitle(Resource::resource->getBundle()->getString("dock"));

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);

	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));
	this->setStation(p_station);
	this->notifyPositionChanged();
}

WindowSelectedStation::~WindowSelectedStation(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Station* WindowSelectedStation::getStation()
{
	return this->mStation;
}

void WindowSelectedStation::setStation( Station* p_station )
{
	if(this->mStation != p_station)
	{
		this->mStation = p_station;
		this->notifyStationChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelectedStation::notifyPositionChanged()
{
	WindowSelected::notifyPositionChanged();
	this->updatePosition();
}

void WindowSelectedStation::notifyStationChanged()
{
	if(this->getStation() != NULL)
	{
		this->setWindowTitle(this->getStation()->getObjectTypeName() + " - " + this->getStation()->getNpcType()->getName());
		this->getStation()->getObjectTypeName() + " - " + this->getStation()->getNpcType()->getName();
		this->mTBNameValue.setText(Resource::resource->getBundle()->getString("station"));
		this->mTBLevelValue.setText(Tools::buildStringWithInt(this->getStation()->getLevel()));

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getStation());
	}
}

void WindowSelectedStation::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->getStation() != NULL)
		{
			for(int i = 0; i < LIFEBAR_COUNT; i++)
				this->mLifeBars[i]->update();	

			if(this->getStation()->getNpcType()->getAlignment() != NpcType::NpcTypeAlignment::AlignmenEvil)
			{
				if(Game::game->getMap()->getMapObjectSelector()->getObjectSelectedDistance() < STATION_DOCK_DISTANCE)
					this->mButtoDock.setEnable(true);
				else
					this->mButtoDock.setEnable(false);
			}
			else
			{
				this->mButtoDock.setEnable(false);
			}
		}
	}
}

void WindowSelectedStation::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);

		this->mButtoDock.update(p_event);
		if(this->mButtoDock.isClicked())
			this->dock();
	}

	WindowSelected::update(p_event);	
}

void WindowSelectedStation::updatePosition()
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

	this->mButtoDock.setX(this->getContentX());
	this->mButtoDock.setY(this->mTBStructure.getBottomY() + BUTTON_OFFSETY);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShield.getY());
	this->mLifeBars[1]->setY(this->mTBArmor.getY());
	this->mLifeBars[2]->setY(this->mTBStructure.getY());
}

void WindowSelectedStation::drawContent()
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
		this->mButtoDock.draw();

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}

void WindowSelectedStation::dock()
{

}
