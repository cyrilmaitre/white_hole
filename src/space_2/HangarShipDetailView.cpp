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
#define BUTTONRENAME_MARGINLEFT			15
#define BUTTONRENAME_BORDERSIZE			1
#define BUTTONRENAME_WIDTH				80
#define BUTTONRENAME_HEIGHT				16
#define WEAPONVIEW_MARGINTOP			50
#define BUTTONPILOT_WIDTH				128
#define BUTTONPILOT_HEIGHT				48
#define BUTTONDROP_MARGIN_LEFT			10


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

	this->mButtonRename.setSize(BUTTONRENAME_WIDTH, BUTTONRENAME_HEIGHT);
	this->mButtonRename.setBorderSize(BUTTONRENAME_BORDERSIZE, true);
	this->mButtonRename.setTitle(Resource::resource->getBundle()->getString("rename"));

	this->mButtonPilot.setSize(BUTTONPILOT_WIDTH, BUTTONPILOT_HEIGHT);
	this->mButtonPilot.setTitle(Resource::resource->getBundle()->getString("pilot"));

	this->mButtonShipSheep.setTitle(Resource::resource->getBundle()->getString("hangarButtonOpenShipSheet"));
	this->mButtonSell.setTitle(Resource::resource->getBundle()->getString("sell"));
	this->mButtonDrop.setTitle(Resource::resource->getBundle()->getString("drop"));
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

HangarShipWeaponView* HangarShipDetailView::getShipWeaponView()
{
	return &this->mWeaponView;
}


//*************************************************************
// Methods
//*************************************************************
void HangarShipDetailView::update()
{
	if(this->isVisible())
	{
		this->mWeaponView.update();
	}
}

void HangarShipDetailView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mButtonRename.update(p_event);
		this->mButtonShipSheep.update(p_event);
		this->mWeaponView.update(p_event);
		this->mButtonSell.update(p_event);
		this->mButtonDrop.update(p_event);
		this->mButtonPilot.update(p_event);
	}
	FieldSet::update(p_event);
}

void HangarShipDetailView::updatePositon()
{
	this->mIcon.setPosition(this->getX() + ICON_MARGIN, this->getY() + ICON_MARGIN);
	this->mTBName.setPosition(this->mIcon.getRightX() + ICON_MARGIN, this->mIcon.getY());
	this->mTBType.setPosition(this->mTBName.getX(), this->mTBName.getBottomY() + TYPE_MARGINTOP);
	this->mTBLevel.setPosition(this->mTBType.getX(), this->mTBType.getBottomY() + LEVEL_MARGINTOP);
	this->mButtonRename.setPosition(this->mTBName.getRightX() + BUTTONRENAME_MARGINLEFT, this->mTBName.getY());
	this->mButtonShipSheep.setPosition(this->getContentX() + this->getContentWidth() - this->mButtonShipSheep.getWidth(), this->getContentY());
	this->mWeaponView.setPosition(this->getContentX(), this->mIcon.getBottomY() + WEAPONVIEW_MARGINTOP);
	this->mButtonSell.setPosition(this->getContentX(), this->getContentY() + this->getContentHeight() - this->mButtonSell.getHeight());
	this->mButtonDrop.setPosition(this->mButtonSell.getRightX() + BUTTONDROP_MARGIN_LEFT, this->getContentY() + this->getContentHeight() - this->mButtonDrop.getHeight());
	this->mButtonPilot.setPosition(this->getContentX() + this->getContentWidth() - this->mButtonPilot.getWidth(), this->getContentY() + this->getContentHeight() - this->mButtonPilot.getHeight());
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
		this->mButtonRename.draw();
		this->mButtonShipSheep.draw();
		this->mWeaponView.draw();
		this->mButtonSell.draw();
		this->mButtonDrop.draw();
		this->mButtonPilot.draw();
	}
}

void HangarShipDetailView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->mWeaponView.setWidth(this->getContentWidth());
	this->updatePositon();
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
		this->mButtonPilot.setEnable(!this->mCharacterShip->isPiloted());
	}
	this->mWeaponView.setCharacterShip(this->mCharacterShip);
	this->setVisible(this->mCharacterShip != NULL);
}