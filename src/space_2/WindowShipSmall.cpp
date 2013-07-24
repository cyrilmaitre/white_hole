#include "WindowShipSmall.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define WINDOW_X					20
#define WINDOW_Y					20
#define WINDOW_WIDTH				293
#define WINDOW_HEIGHT				64				
#define TB_LABEL_FONTCOLOR			sf::Color(195,195,195)
#define TB_LABEL_FONTSIZE			ManagerConfig::FontSize::Small
#define TB_LABEL_OFFSETY			10
#define LIFEBAR_OFFSETX				90
#define LIFEBAR_WIDTH				200
#define LIFEBAR_HEIGHT				14



//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowShipSmall::WindowShipSmall(void)
{
	this->mTBShieldLabel = NULL;
	this->mTBArmorLabel = NULL;
	this->mTBStructureLabel = NULL;
	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i] = NULL;
	this->mCharacterShip = NULL;

	this->mTBShieldLabel = new TextBox();
	this->mTBArmorLabel = new TextBox();
	this->mTBStructureLabel = new TextBox();

	this->mTBShieldLabel->setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBShieldLabel->setFontSize(TB_LABEL_FONTSIZE);
	this->mTBShieldLabel->setText(Resource::resource->getBundle()->getString("uigShipSmallShieldLabel"));
	this->mTBArmorLabel->setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBArmorLabel->setFontSize(TB_LABEL_FONTSIZE);
	this->mTBArmorLabel->setText(Resource::resource->getBundle()->getString("uigShipSmallArmorLabel"));
	this->mTBStructureLabel->setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBStructureLabel->setFontSize(TB_LABEL_FONTSIZE);
	this->mTBStructureLabel->setText(Resource::resource->getBundle()->getString("uigShipSmallStructureLabel"));

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);

	this->setX(WINDOW_X);
	this->setY(WINDOW_Y);
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeStaticLeft);
	this->setOpen(true);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_SHIP));
}

WindowShipSmall::~WindowShipSmall(void)
{
	if(this->mTBShieldLabel != NULL)
		delete this->mTBShieldLabel;

	if(this->mTBArmorLabel != NULL)
		delete this->mTBArmorLabel;

	if(this->mTBStructureLabel != NULL)
		delete this->mTBStructureLabel;

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		if(this->mLifeBars[i] != NULL)
			delete this->mLifeBars[i];
}


//*************************************************************
// Methods
//*************************************************************
CharacterShip* WindowShipSmall::getCharacterShip()
{
	return this->mCharacterShip;
}

void WindowShipSmall::setCharacterShip( CharacterShip *p_ship )
{
	this->mCharacterShip = p_ship;
	this->notifyCharacterShipChanged();
}


//*************************************************************
// Methods
//*************************************************************
void WindowShipSmall::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->updatePosition();
}

void WindowShipSmall::notifyCharacterShipChanged()
{
	if(this->mCharacterShip != NULL)
	{
		this->setWindowTitle(this->getCharacterShip()->getCharacter()->getName() + " - " + this->getCharacterShip()->getShipModel()->getName());
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getCharacterShip());
	}
}

void WindowShipSmall::updatePosition()
{
	this->mTBShieldLabel->setX(this->getContentX());
	this->mTBShieldLabel->setY(this->getContentY());
	this->mTBArmorLabel->setX(this->getContentX());
	this->mTBArmorLabel->setY(this->mTBShieldLabel->getY() + this->mTBShieldLabel->getHeight() + TB_LABEL_OFFSETY);
	this->mTBStructureLabel->setX(this->getContentX());
	this->mTBStructureLabel->setY(this->mTBArmorLabel->getY() + this->mTBArmorLabel->getHeight() + TB_LABEL_OFFSETY);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShieldLabel->getY());
	this->mLifeBars[1]->setY(this->mTBArmorLabel->getY());
	this->mLifeBars[2]->setY(this->mTBStructureLabel->getY());
}

void WindowShipSmall::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update();
	}
}	

void WindowShipSmall::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);
	}
	Window::update(p_event);
}

void WindowShipSmall::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		// Draw label
		this->mTBShieldLabel->draw();
		this->mTBArmorLabel->draw();
		this->mTBStructureLabel->draw();

		// Draw life bars
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}

