#include "WindowCargoLoot.h"
#include "Game.h"


//*************************************************************
// Define
//*************************************************************
#define BUTTON_WIDTH				80
#define BUTTON_HEIGHT				18
#define BOTTOM_HEIGHT				26
#define SPRITECREDIT_OFFSETY		10
#define TEXTBOXCREDIT_COLOR			sf::Color(255, 255, 255)
#define TEXTBOXCREDIT_FONTSIZE		ManagerConfig::FontSize::Small
#define TEXTBOXCREDIT_OFFSETX		5
#define TEXTBOXCREDIT_OFFSETY		10
#define BUTTON_BOTTOM_OFFSETX		10
#define BUTTON_BOTTOM_OFFSETY		10
#define BUTTON_BOTTOM_WIDTH			80
#define BUTTON_BOTTOM_HEIGHT		18


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowCargoLoot::WindowCargoLoot( void )
{
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(Resource::resource->getBundle()->getString("windowsTitleCargoLoot"));
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_NINESQUARE));

	this->mSpriteCredit = SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_CREDIT);
	this->mTBCredit.setFontColor(TEXTBOXCREDIT_COLOR);
	this->mTBCredit.setFontSize(TEXTBOXCREDIT_FONTSIZE);

	this->mButtonLootCredit.setTitle(Resource::resource->getBundle()->getString("lootCredit"));
	this->mButtonLootCredit.setWidth(BUTTON_BOTTOM_WIDTH);
	this->mButtonLootCredit.setHeight(BUTTON_BOTTOM_HEIGHT);
	
	this->mButtonLootAll.setTitle(Resource::resource->getBundle()->getString("lootAll"));
	this->mButtonLootAll.setWidth(BUTTON_BOTTOM_WIDTH);
	this->mButtonLootAll.setHeight(BUTTON_BOTTOM_HEIGHT);

	this->mContainerView = new ContainerView();
	this->notifyContainerViewChanged();

	this->setPositionMiddleScreen();
}

WindowCargoLoot::~WindowCargoLoot(void)
{
	delete this->mContainerView;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerView* WindowCargoLoot::getContainerView()
{
	return this->mContainerView;
}

Wreck* WindowCargoLoot::getWreck()
{
	return this->mWreck;
}	

void WindowCargoLoot::setWreck( Wreck* p_wreck )
{
	this->mWreck = p_wreck;
	this->notifyWreckChanged();
}


//*************************************************************
// Methods
//*************************************************************
void WindowCargoLoot::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->mContainerView->setX(this->getContentX());
	this->mContainerView->setY(this->getContentY());

	this->mSpriteCredit.setPosition(this->getContainerView()->getX(), 
									this->getContainerView()->getY() + this->getContainerView()->getHeight() + SPRITECREDIT_OFFSETY);

	this->mTBCredit.setPosition(this->getContainerView()->getX() + this->mSpriteCredit.getLocalBounds().width + TEXTBOXCREDIT_OFFSETX,
								this->getContainerView()->getY() + this->getContainerView()->getHeight() + TEXTBOXCREDIT_OFFSETY);

	this->mButtonLootAll.setPosition(	this->getContainerView()->getX() + this->getContainerView()->getWidth() - this->mButtonLootAll.getWidth(),
										this->getContainerView()->getY() + this->getContainerView()->getHeight() + BUTTON_BOTTOM_OFFSETY);

	this->mButtonLootCredit.setPosition(this->mButtonLootAll.getX() - this->mButtonLootCredit.getWidth() - BUTTON_BOTTOM_OFFSETX,
										this->getContainerView()->getY() + this->getContainerView()->getHeight() + BUTTON_BOTTOM_OFFSETY);				
}

void WindowCargoLoot::notifyContainerViewChanged()
{
	this->setContentHeight(this->mContainerView->getHeight() + BOTTOM_HEIGHT);
	this->setContentWidth(this->mContainerView->getWidth());
	this->notifyPositionChanged();
}

void WindowCargoLoot::notifyWreckChanged()
{
	if(this->getWreck() != NULL)
		this->mTBCredit.setText(Tools::formatNumber(this->getWreck()->getCredit()));

	this->getContainerView()->setContainerable(this->getWreck());
}

void WindowCargoLoot::update()
{
	if(this->mContainerView->isContainerableChanged())
		this->notifyContainerViewChanged();

	if(this->isOpen() && !this->isReduce())
		this->mContainerView->update();
}

void WindowCargoLoot::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonLootAll.update(p_event);
		this->mButtonLootCredit.update(p_event);
		this->mContainerView->update(p_event);

		if(this->mButtonLootCredit.isClicked())
		{
			Game::game->getCharacter()->incCredit(this->getWreck()->getCredit());
			this->getWreck()->setCredit(0);
			this->notifyWreckChanged();
		}
	}
	Window::update(p_event);
}

void WindowCargoLoot::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mContainerView->draw();
		
		Resource::resource->getApp()->draw(this->mSpriteCredit);
		this->mTBCredit.draw();
		this->mButtonLootCredit.draw();
		this->mButtonLootAll.draw();
	}
}




