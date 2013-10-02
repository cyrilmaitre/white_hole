#include "HangarShipDetailView.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR					sf::Color(25, 26, 28)
#define BORDERCOLOR						sf::Color(194, 194, 194)
#define BORDERSIZE						1
#define PADDING							10
#define ICON_MARGIN						7
#define ICON_WIDTH						64
#define ICON_HEIGHT						64
#define ICON_BACKGROUNDCOLOR			sf::Color(65, 65, 65)
#define ICON_BORD_COLOR					sf::Color(128, 128, 128, 125)
#define ICON_BORD_SIZE					2
#define NAME_FONTSIZE					18
#define TYPE_FONTSIZE					14
#define TYPE_MARGINTOP					5
#define LEVEL_FONTSIZE					18
#define LEVEL_MARGINTOP					10


//*************************************************************
// Constructor - Destructor
//*************************************************************
HangarShipDetailView::HangarShipDetailView(void)
{
	this->mCharacterShip = NULL;

	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);

	this->mIcon.setSize(ICON_WIDTH, ICON_HEIGHT);
	this->mIcon.setBackgroundColor(ICON_BACKGROUNDCOLOR, true);
	this->mIcon.setBorderColor(ICON_BORD_COLOR, true);
	this->mIcon.setBorderSize(ICON_BORD_SIZE, true);

	this->mTBName.setFontSize(NAME_FONTSIZE);
	this->mTBType.setFontSize(TYPE_FONTSIZE);
	this->mTBLevel.setFontSize(LEVEL_FONTSIZE);
}

HangarShipDetailView::~HangarShipDetailView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
CharacterShip* HangarShipDetailView::getCharacterShip()
{
	return this->mCharacterShip;
}

void HangarShipDetailView::setCharacterShip( CharacterShip* p_ship )
{
	if(this->mCharacterShip != p_ship)
	{
		this->mCharacterShip = p_ship;
		this->notifyCharacterShipChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipDetailView::update()
{
	if(this->isVisible())
	{

	}
}

void HangarShipDetailView::update( sf::Event p_event )
{
	if(this->isVisible())
	{

	}
	FieldSet::update(p_event);
}

void HangarShipDetailView::updatePositon()
{
	this->mIcon.setPosition(this->getX() + ICON_MARGIN, this->getY() + ICON_MARGIN);
	this->mTBName.setPosition(this->mIcon.getRightX() + ICON_MARGIN, this->mIcon.getY());
	this->mTBType.setPosition(this->mTBName.getX(), this->mTBName.getBottomY() + TYPE_MARGINTOP);
	this->mTBLevel.setPosition(this->mTBType.getX(), this->mTBType.getBottomY() + LEVEL_MARGINTOP);
}

void HangarShipDetailView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mIcon.draw();
		this->mTBName.draw();
		this->mTBType.draw();
		this->mTBLevel.draw();
	}
}

void HangarShipDetailView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePositon();
}

void HangarShipDetailView::notifyCharacterShipChanged()
{
	if(this->mCharacterShip != NULL)
	{
		this->mIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->mCharacterShip->getShipModel()->getSpriteId()));
		this->mTBName.setText(this->mCharacterShip->getName());
		this->mTBType.setText(this->mCharacterShip->getShipModel()->getName());
		this->mTBLevel.setText(Resource::resource->getBundle()->getString("level") + ":" + Tools::getSpaceAfterColon() + Tools::formatNumber(this->mCharacterShip->getLevel()));
	}
}