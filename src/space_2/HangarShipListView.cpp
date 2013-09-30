#include "HangarShipListView.h"
#include "Tools.h"


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
#define ICONPILOTED_WIDTH			16
#define ICONPILOTED_HEIGHT			16
#define ICONPILOTED_BACKCOLOR		sf::Color(255, 255, 255, 0)
#define ICONPILOTED_BORDSIZE		0
#define ICONPILOTED_MARGIN			5
#define NAME_FONTSIZE				18
#define TYPE_FONTSIZE				14
#define TYPE_MARGINTOP				5
#define LEVEL_FONTSIZE				18
#define LEVEL_MARGINTOP				10


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarShipListView::HangarShipListView( CharacterShip* p_ship )
{
	this->mShip = NULL;

	this->mIcon.setSize(ICON_WIDTH, ICON_HEIGHT);
	this->mIcon.setBackgroundColor(ICON_BACKGROUNDCOLOR, true);
	this->mIcon.setBorderColor(ICON_BORD_COLOR, true);
	this->mIcon.setBorderSize(ICON_BORD_SIZE, true);

	this->mIconPiloted.setSize(ICONPILOTED_WIDTH, ICONPILOTED_HEIGHT);
	this->mIconPiloted.setBackgroundColor(ICONPILOTED_BACKCOLOR, true);
	this->mIconPiloted.setBorderSize(ICONPILOTED_BORDSIZE, true);
	this->mIconPiloted.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSpritePtr(IC_16X16_SHIPLIGHT));

	this->mTBName.setFontSize(NAME_FONTSIZE);
	this->mTBType.setFontSize(TYPE_FONTSIZE);
	this->mTBLevel.setFontSize(LEVEL_FONTSIZE);

	this->setSize(HANGARSHIPLISTVIEW_WIDTH, HEIGHT);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBackgroundColorOver(BACKGROUNDCOLOR_OVER);

	this->setShip(p_ship);
}

HangarShipListView::~HangarShipListView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CharacterShip* HangarShipListView::getShip()
{
	return this->mShip;
}

void HangarShipListView::setShip( CharacterShip* p_ship )
{
	if(this->mShip != p_ship)
	{
		this->mShip = p_ship;
		this->notifyShipChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipListView::update()
{
}

void HangarShipListView::update( sf::Event p_event )
{
	Listable::update(p_event);
}

void HangarShipListView::updatePosition()
{
	this->mIcon.setPosition(this->getX() + ICON_MARGIN, this->getY() + ICON_MARGIN);
	this->mIconPiloted.setPosition(this->getRightX() - ICONPILOTED_WIDTH - ICONPILOTED_MARGIN, this->getY() + ICONPILOTED_MARGIN);
	this->mTBName.setPosition(this->mIcon.getRightX() + ICON_MARGIN, this->mIcon.getY());
	this->mTBType.setPosition(this->mTBName.getX(), this->mTBName.getBottomY() + TYPE_MARGINTOP);
	this->mTBLevel.setPosition(this->mTBType.getX(), this->mTBType.getBottomY() + LEVEL_MARGINTOP);
}

void HangarShipListView::draw()
{
	Listable::draw();
	if(this->isVisible())
	{
		this->mIcon.draw();
		this->mTBName.draw();
		this->mTBType.draw();
		this->mTBLevel.draw();
		this->mIconPiloted.draw();
	}
}

void HangarShipListView::notifyShipChanged()
{
	if(this->mShip != NULL)
	{
		this->mIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->mShip->getShipModel()->getSpriteId()));
		this->mTBName.setText(this->mShip->getName());
		this->mTBType.setText(this->mShip->getShipModel()->getName());
		this->mTBLevel.setText(Resource::resource->getBundle()->getString("level") + ":" + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mShip->getLevel()));
		this->mIconPiloted.setVisible(this->mShip->isPiloted());
	}
}

void HangarShipListView::notifyPositionChanged()
{
	Listable::notifyPositionChanged();
	this->updatePosition();
}

void HangarShipListView::notifySelectedChanged()
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