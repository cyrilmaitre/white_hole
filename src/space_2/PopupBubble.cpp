#include "PopupBubble.h"
#include "Manager.h"

//******************************
// Define
//******************************
#define ARROW_WIDTH						20
#define ARROW_HEIGHT					11
#define DEFAULT_BACKGROUNDCOLOR			sf::Color(0, 0, 0, 200)
#define DEFAULT_BORDERSIZE				1
#define DEFAULT_BORDERCOLOR				sf::Color(150, 150, 150, 200)
#define DEFAULT_PADDING					5
#define DEFAULT_DELAY					400


//******************************
// Statics init
//******************************
std::list<PopupBubble*> PopupBubble::mPopupBubbles;


//******************************
// Constructor - Destructor
//******************************
PopupBubble::PopupBubble( Object* p_trigger ) : TextMultiLine(true)
{
	this->setVisible(false);
	this->setAutoResizeWidth(true);
	this->mTrigger = p_trigger;
	this->mDelay = DEFAULT_DELAY;

	this->mPopupBubbleArrow.setTexture(*Manager::getInstance()->getConfig()->getTexturePopupBubbleArrow());
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);
	this->setBorderSize(DEFAULT_BORDERSIZE);
	this->setPadding(DEFAULT_PADDING);

	PopupBubble::mPopupBubbles.push_back(this);
}

PopupBubble::~PopupBubble(void)
{
	PopupBubble::mPopupBubbles.remove(this);
}


//******************************
// Getters - Setters
//******************************
double PopupBubble::getDelay()
{
	return this->mDelay;
}

void PopupBubble::setDelay( double p_delay )
{
	this->mDelay = p_delay;
}

void PopupBubble::setArrowPointerX( int p_x )
{
	Object::setX(p_x - (this->getWidth() / 2));
}

void PopupBubble::setArrowPointerY( int p_y )
{
	Object::setY(p_y - this->getHeight() - ARROW_HEIGHT);
}


//******************************
// Methods
//******************************
void PopupBubble::notifyPositionChanged()
{
	TextMultiLine::notifyPositionChanged();
	this->updateArrowPosition();
}

void PopupBubble::notifySizeChanged()
{
	TextMultiLine::notifySizeChanged();
	this->updateArrowPosition();
}

void PopupBubble::notifyVisibleChanged()
{
	TextMultiLine::notifyVisibleChanged();
	if(this->isVisible())
	{
		this->setArrowPointerX(this->mTrigger->getX() + (this->mTrigger->getWidth() / 2));
		this->setArrowPointerY(this->mTrigger->getY());
	}
}

void PopupBubble::update()
{
	// Reset if mouse over changed
	if(this->mTrigger->isMouseOverChanged())
		this->mClockDelay.restart();

	// Set visible... or not
	if(this->mTrigger->hasMouseOver())
	{
		if(this->mClockDelay.getElapsedTimeAsMilliseconds() > this->mDelay)
			this->setVisible(true);
	}
	else
		this->setVisible(false);
}

void PopupBubble::update(sf::Event p_event)
{
	TextMultiLine::update(p_event);
}

void PopupBubble::updateArrowPosition()
{
	this->mPopupBubbleArrow.setPosition(this->getX() + (this->getWidth() - ARROW_WIDTH) / 2, this->getY() + this->getHeight());
}

void PopupBubble::draw()
{
	if(this->isVisible() && this->mTrigger->isEnable())
	{
		TextMultiLine::draw();
		Resource::resource->getApp()->draw(this->mPopupBubbleArrow);
	}
}

void PopupBubble::drawAll()
{
	std::list<PopupBubble*>::iterator current;
	for( current = PopupBubble::mPopupBubbles.begin(); current != PopupBubble::mPopupBubbles.end(); current++ )
	{
		(*current)->draw();
	}
}

