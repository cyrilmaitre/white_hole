#include "RaceView.h"
#include "SpriteParameterFactory.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define RACEVIEW_WIDTH					80
#define RACEVIEW_HEIGHT					96
#define RACEVIEW_IMG_WIDTH				72
#define RACEVIEW_IMG_HEIGHT				72
#define RACEVIEW_IMG_OFFSETY			5
#define RACEVIEW_BACKCOLOR				sf::Color(128, 128, 128, 75)
#define RACEVIEW_BORDSIZE				2
#define RACEVIEW_BORDSIZE_SELECTED		2
#define RACEVIEW_BORDCOLOR				sf::Color(128, 128, 128, 125)
#define RACEVIEW_BORDCOLOR_OVER			sf::Color(128, 128, 128, 125)
#define RACEVIEW_BORDCOLOR_SELECTED		sf::Color(255, 106, 0, 125)
#define RACEVIEW_TB_NAME_FONTSIZE		ManagerConfig::FontSize::Tiny
#define RACEVIEW_TB_NAME_FONTCOLOR		sf::Color(195,195,195)
#define RACEVIEW_TB_NAME_OFFSETY		5
#define RACEVIEW_OVERLAY_COLOR			sf::Color(48, 48, 48, 120)


//*************************************************************
// Constructor - Destructor
//*************************************************************
RaceView::RaceView( Race *p_race, double p_x, double p_y )
{
	this->mRaceSprite = NULL;

	this->mTBName = new TextBox();
	this->mTBName->setFontSize(RACEVIEW_TB_NAME_FONTSIZE);
	this->mTBName->setFontColor(RACEVIEW_TB_NAME_FONTCOLOR);

	this->setSize(RACEVIEW_WIDTH, RACEVIEW_HEIGHT);
	this->setBackgroundColor(RACEVIEW_BACKCOLOR, true);

	this->mOverlayOver.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mOverlayOver.setFillColor(RACEVIEW_OVERLAY_COLOR);

	this->setRace(p_race);
	this->setSelectable(false);
}

RaceView::~RaceView(void)
{
	if(this->mRaceSprite != NULL)
		delete this->mRaceSprite;

	if(this->mTBName != NULL)
		delete this->mTBName;
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool RaceView::hasRace()
{
	return this->mRace != NULL;
}

Race* RaceView::getRace()
{
	return this->mRace;
}

void RaceView::setRace( Race *p_race )
{
	this->mRace = p_race;
	this->notifyRaceChanged();
}

bool RaceView::isSelectable()
{
	return this->mSelectable;
}

void RaceView::setSelectable( bool p_selectable )
{
	this->mSelectable = p_selectable;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void RaceView::update( sf::Event myEvent )
{
	if(this->isVisible())
	{
		Block::update(myEvent);
	}
}

void RaceView::updatePosition()
{
	// Update race sprite
	int raceSpriteOffsetX = (this->getWidth() - this->mRaceSprite->getGlobalBounds().width) / 2;
	this->mRaceSprite->setPosition(this->getX() + raceSpriteOffsetX, this->getY() + RACEVIEW_IMG_OFFSETY);

	// Update race name
	this->mTBName->setX(this->getX() + (this->getWidth() - this->mTBName->getWidth()) / 2);
	this->mTBName->setY(this->getY() + this->getHeight() - this->mTBName->getHeight() - RACEVIEW_TB_NAME_OFFSETY);

	// Update overlay
	this->mOverlayOver.setPosition(this->getX(), this->getY());
}

void RaceView::draw()
{
	if(this->isVisible())
	{
		// Draw Selectable
		if(!this->isSelected())
		{
			this->setBorderSize(RACEVIEW_BORDSIZE, true);
			this->setBorderColor(RACEVIEW_BORDCOLOR);
			this->setBorderColorOver(RACEVIEW_BORDCOLOR_OVER);
			this->setBorderColorFocus(RACEVIEW_BORDCOLOR);
		}
		else
		{
			this->setBorderSize(RACEVIEW_BORDSIZE_SELECTED, true);
			this->setBorderColor(RACEVIEW_BORDCOLOR_SELECTED, true);
		}
		Block::draw();

		// Draw race sprite
		Resource::resource->getApp()->draw(*this->mRaceSprite);

		// Draw race name
		this->mTBName->draw();

		// Draw overlay
		if(this->isSelectable() && !this->isSelected() && !this->hasMouseOver())
			Resource::resource->getApp()->draw(this->mOverlayOver);
	}
}

void RaceView::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updatePosition();
}

void RaceView::notifyRaceChanged()
{
	if(this->hasRace())
	{
		if(this->mRaceSprite != NULL)
			delete this->mRaceSprite;
		this->mRaceSprite = SpriteParameterFactory::getSpriteParameterRace(true)->getSpritePtr(this->getRace()->getSpriteId(), RACEVIEW_IMG_WIDTH, RACEVIEW_IMG_HEIGHT);
		this->mTBName->setText(this->getRace()->getName());
		this->updatePosition();
	}
}

