#include "MarketItemListView.h"


//*************************************************************
// Define
//*************************************************************
#define HEIGHT						ICON_HEIGHT + ICON_MARGIN * 2
#define BACKGROUNDCOLOR				sf::Color(255, 255, 255, 0)
#define BACKGROUNDCOLOR_OVER		sf::Color(37, 37, 37)
#define BACKGROUNDCOLOR_SELECTED	sf::Color(90, 90, 90)
#define ICON_MARGIN					7
#define ICON_WIDTH					64
#define ICON_HEIGHT					64
#define ICON_BACKGROUNDCOLOR		sf::Color(65, 65, 65)
#define ICON_BORD_COLOR				sf::Color(128, 128, 128, 125)
#define ICON_BORD_SIZE				2
#define NAME_FONTSIZE				16


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemListView::MarketItemListView( Item* p_item )
{
	this->mItem = NULL;

	this->mIcon.setSize(ICON_WIDTH, ICON_HEIGHT);
	this->mIcon.setBackgroundColor(ICON_BACKGROUNDCOLOR, true);
	this->mIcon.setBorderColor(ICON_BORD_COLOR, true);
	this->mIcon.setBorderSize(ICON_BORD_SIZE, true);

	this->setSize(MARKETITEMLISTVIEW_WIDTH, HEIGHT);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBackgroundColorOver(BACKGROUNDCOLOR_OVER);

	this->setItem(p_item);
}

MarketItemListView::~MarketItemListView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Item* MarketItemListView::getItem()
{
	return this->mItem;
}

void MarketItemListView::setItem( Item* p_item )
{
	if(this->mItem != p_item)
	{
		this->mItem = p_item;
		this->notifyItemChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarketItemListView::updatePosition()
{
	this->mIcon.setPosition(this->getX() + ICON_MARGIN, this->getY() + ICON_MARGIN);
	this->mTBName.setPosition(this->mIcon.getRightX() + ICON_MARGIN, this->mIcon.getY());
}

void MarketItemListView::update( sf::Event p_event )
{
	Listable::update(p_event);
}

void MarketItemListView::draw()
{
	Listable::draw();

	if(this->isVisible())
	{
		this->mIcon.draw();
		this->mTBName.draw();
	}
}

void MarketItemListView::notifyItemChanged()
{
	if(this->getItem() != NULL)
	{
		this->mIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getItem()->getSpriteId()));
		this->mTBName.setText(this->getItem()->getName());
	}
}

void MarketItemListView::notifyPositionChanged()
{
	Listable::notifyPositionChanged();
	this->updatePosition();
}

void MarketItemListView::notifySelectedChanged()
{
	Selectable::notifySelectedChanged();
	if(this->isSelected())
	{
		this->setBackgroundColor(BACKGROUNDCOLOR_SELECTED, true);
	}
	else
	{
		this->setBackgroundColor(BACKGROUNDCOLOR, true);
		this->setBackgroundColorOver(BACKGROUNDCOLOR_OVER);
	}
}

