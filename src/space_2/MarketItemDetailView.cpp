#include "MarketItemDetailView.h"


//*************************************************************
// Define
//*************************************************************
#define HEIGHT						300
#define BACKGROUNDCOLOR				sf::Color(25, 26, 28)
#define BORDERCOLOR					sf::Color(255, 255, 255, 0)
#define BORDERSIZE					0
#define PADDING						10
#define ICON_MARGIN					7
#define ICON_WIDTH					64
#define ICON_HEIGHT					64
#define ICON_BACKGROUNDCOLOR		sf::Color(65, 65, 65)
#define ICON_BORD_COLOR				sf::Color(128, 128, 128, 125)
#define ICON_BORD_SIZE				2
#define NAME_FONTSIZE				22
#define TIER_FONTSIZE				14
#define TIER_MARGINTOP				5
#define ARIANE_MARGIN				10
#define DESCRIPTION_HEIGHTMAX		150


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemDetailView::MarketItemDetailView(void)
{
	this->mItem != NULL;

	this->setVisible(false);
	this->setHeight(HEIGHT);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setDisplayTitle(false);
	this->setPadding(PADDING);

	this->mIcon.setSize(ICON_WIDTH, ICON_HEIGHT);
	this->mIcon.setBackgroundColor(ICON_BACKGROUNDCOLOR, true);
	this->mIcon.setBorderColor(ICON_BORD_COLOR, true);
	this->mIcon.setBorderSize(ICON_BORD_SIZE, true);

	this->mTBName.setFontSize(NAME_FONTSIZE);
	this->mTBTier.setFontSize(TIER_FONTSIZE);
	this->mTBDescription.setAutoResizeHeight(true);
	this->mTBDescription.setAutoResizeHeightMax(DESCRIPTION_HEIGHTMAX);
	this->mTBDescription.setAutoResizeWidth(false);

	this->mButtonMoreInfo.setTitle(Resource::resource->getBundle()->getString("marketBuyMoreInfo"));
}

MarketItemDetailView::~MarketItemDetailView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Item* MarketItemDetailView::getItem()
{
	return this->mItem;
}

void MarketItemDetailView::setItem( Item* p_item )
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
void MarketItemDetailView::updatePosition()
{
	this->mIcon.setPosition(this->getContentX(), this->getContentY());
	this->mTBName.setPosition(this->mIcon.getRightX() + ICON_MARGIN, this->mIcon.getY());
	this->mTBArianeType.setPosition(this->mTBName.getRightX() + ARIANE_MARGIN, this->mTBName.getBottomY() - this->mTBArianeType.getHeight());
	this->mTBTier.setPosition(this->mTBName.getX(), this->mTBName.getBottomY() + TIER_MARGINTOP);
	this->mButtonMoreInfo.setPosition(this->getContentX() + this->getContentWidth() - this->mButtonMoreInfo.getWidth(), this->getContentY());
	this->mTBDescription.setPosition(this->getContentX(), this->mIcon.getBottomY() + ICON_MARGIN);
}

void MarketItemDetailView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTBDescription.update(p_event);
		this->mButtonMoreInfo.update(p_event);
	}
	FieldSet::update(p_event);
}

void MarketItemDetailView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mIcon.draw();
		this->mTBName.draw();
		this->mTBTier.draw();
		this->mButtonMoreInfo.draw();
		this->mTBArianeType.draw();
		this->mTBDescription.draw();
	}
}

void MarketItemDetailView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void MarketItemDetailView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->mTBDescription.setWidth(this->getContentWidth());
	this->mTBDescription.updateLine();
	this->updatePosition();
}

void MarketItemDetailView::notifyItemChanged()
{
	if(this->getItem() != NULL)
	{
		this->setVisible(true);
		
		this->mIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getItem()->getSpriteId()));
		this->mTBName.setText(this->getItem()->getName());
		this->mTBTier.setText(this->getItem()->getItemTier()->getName());
		this->mTBTier.setFontColor(this->getItem()->getItemTier()->getColor());
		this->mTBArianeType.setText("(" + this->getItem()->getItemType()->getAriane() + ")");
		this->mTBDescription.setText(this->getItem()->getDescription());

		this->updatePosition();
	}
	else
	{
		this->setVisible(false);
	}
}
