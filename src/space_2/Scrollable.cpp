#include "Scrollable.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
Scrollable::Scrollable()
{
	this->mScrollBar = NULL;
	this->mScrollBar = new Scrollbar();
	this->mScrollBar->setVisible(false);
	this->setMouseOverForced(true);

	this->mForceScrollbar = false;
}

Scrollable::~Scrollable(void)
{
	if(this->mScrollBar != NULL)
		delete this->mScrollBar;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Scrollbar* Scrollable::getScrollbar()
{
	return this->mScrollBar;
}

bool Scrollable::hasScrollBar()
{
	return this->isForceScrollbar() || this->mScrollBar->isUsefull();
}

bool Scrollable::isForceScrollbar()
{
	return this->mForceScrollbar;
}

void Scrollable::setForceScrollBar( bool p_forced )
{
	if(this->mForceScrollbar != p_forced)
	{
		this->mForceScrollbar = p_forced;
		this->notifyForceScrollbarChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void Scrollable::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mScrollBar->update(p_event);
		Block::update(p_event);

		if(this->hasMouseOver())
		{
			if(p_event.type == sf::Event::MouseWheelMoved)
			{
				int delta = p_event.mouseWheel.delta;
				bool up = delta > 0;
				delta = Tools::getAbsolute(delta);

				while(delta > 0)
				{
					this->notifyScrollOccured(up);
					delta--;
				}
			}
		}
	}
}

void Scrollable::notifyForceScrollbarChanged()
{
	if(this->isForceScrollbar())
		this->mScrollBar->setVisible(true);
}

void Scrollable::updateScrollbarVisibility()
{
	this->mScrollBar->setVisible(this->hasScrollBar());
}

void Scrollable::notifyScrollOccured( bool p_up )
{
	if(p_up)
		this->mScrollBar->scrollUp();
	else
		this->mScrollBar->scrollDown();
}

void Scrollable::draw()
{
	if(this->isVisible())
	{
		Block::draw();
		this->mScrollBar->draw();
	}
}

