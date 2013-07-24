#include "JobView.h"
#include "SpriteParameterFactory.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define JOBVIEW_WIDTH					80
#define JOBVIEW_HEIGHT					96
#define JOBVIEW_IMG_WIDTH				72
#define JOBVIEW_IMG_HEIGHT				72
#define JOBVIEW_IMG_OFFSETY				5
#define JOBVIEW_BACKCOLOR				sf::Color(128, 128, 128, 75)
#define JOBVIEW_BORDSIZE				2
#define JOBVIEW_BORDSIZE_SELECTED		2
#define JOBVIEW_BORDCOLOR				sf::Color(128, 128, 128, 125)
#define JOBVIEW_BORDCOLOR_OVER			sf::Color(128, 128, 128, 125)
#define JOBVIEW_BORDCOLOR_SELECTED		sf::Color(255, 106, 0, 125)
#define JOBVIEW_TB_NAME_FONTSIZE		ManagerConfig::FontSize::Tiny	
#define JOBVIEW_TB_NAME_FONTCOLOR		sf::Color(195,195,195)
#define JOBVIEW_TB_NAME_OFFSETY			5
#define JOBVIEW_OVERLAY_COLOR			sf::Color(48, 48, 48, 120)


//*************************************************************
// Constructor - Destructor
//*************************************************************
JobView::JobView( Job *p_job, double p_x, double p_y )
{
	this->mJobSprite = NULL;

	this->mTBName = new TextBox();
	this->mTBName->setFontSize(JOBVIEW_TB_NAME_FONTSIZE);
	this->mTBName->setFontColor(JOBVIEW_TB_NAME_FONTCOLOR);

	this->setSize(JOBVIEW_WIDTH, JOBVIEW_HEIGHT);
	this->setBackgroundColor(JOBVIEW_BACKCOLOR, true);

	this->mOverlayOver.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mOverlayOver.setFillColor(JOBVIEW_OVERLAY_COLOR);

	this->setJob(p_job);
	this->setSelectable(false);
}


JobView::~JobView(void)
{
	if(this->mJobSprite != NULL)
		delete this->mJobSprite;

	if(this->mTBName != NULL)
		delete this->mTBName;
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool JobView::hasJob()
{
	return this->mJob != NULL;
}

Job * JobView::getJob()
{
	return this->mJob;
}

void JobView::setJob( Job *p_job )
{
	this->mJob = p_job;
	this->notifyJobChanged();
}

bool JobView::isSelectable()
{
	return this->mSelectable;
}

void JobView::setSelectable( bool p_selectable )
{
	this->mSelectable = p_selectable;
}


//*************************************************************
// Methods
//*************************************************************
void JobView::update( sf::Event myEvent )
{
	if(this->isVisible())
	{
		Block::update(myEvent);
	}
}

void JobView::updatePosition()
{
	// Update job sprite
	int jobSpriteOffsetX = (this->getWidth() - this->mJobSprite->getGlobalBounds().width) / 2;
	this->mJobSprite->setPosition(this->getX() + jobSpriteOffsetX, this->getY() + JOBVIEW_IMG_OFFSETY);

	// Update job name
	this->mTBName->setX(this->getX() + (this->getWidth() - this->mTBName->getWidth()) / 2);
	this->mTBName->setY(this->getY() + this->getHeight() - this->mTBName->getHeight() - JOBVIEW_TB_NAME_OFFSETY);

	// Update overlay
	this->mOverlayOver.setPosition(this->getX(), this->getY());
}

void JobView::draw()
{
	if(this->isVisible() && this->hasJob())
	{
		// Draw Selectable
		if(!this->isSelected())
		{
			this->setBorderSize(JOBVIEW_BORDSIZE, true);
			this->setBorderColor(JOBVIEW_BORDCOLOR);
			this->setBorderColorOver(JOBVIEW_BORDCOLOR_OVER);
			this->setBorderColorFocus(JOBVIEW_BORDCOLOR);
		}
		else
		{
			this->setBorderSize(JOBVIEW_BORDSIZE_SELECTED, true);
			this->setBorderColor(JOBVIEW_BORDCOLOR_SELECTED, true);
		}
		Block::draw();

		// Draw job sprite
		Resource::resource->getApp()->draw(*this->mJobSprite);

		// Draw job name
		this->mTBName->draw();

		// Draw overlay
		if(this->isSelectable() && !this->isSelected() && !this->hasMouseOver())
			Resource::resource->getApp()->draw(this->mOverlayOver);
	}
}

void JobView::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updatePosition();
}

void JobView::notifyJobChanged()
{
	if(this->hasJob())
	{
		if(this->mJobSprite != NULL)
			delete this->mJobSprite;
		this->mJobSprite = SpriteParameterFactory::getSpriteParameterJob(true)->getSpritePtr(this->getJob()->getSpriteId(), JOBVIEW_IMG_WIDTH, JOBVIEW_IMG_HEIGHT);
		this->mTBName->setText(this->getJob()->getName());
		this->updatePosition();
	}
}


