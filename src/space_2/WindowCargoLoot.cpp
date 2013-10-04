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

	this->mContainerableView = new ContainerableView();
	this->notifyContainerableViewChanged();

	this->setPositionMiddleScreen();
}

WindowCargoLoot::~WindowCargoLoot(void)
{
	delete this->mContainerableView;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerableView* WindowCargoLoot::getContainerableView()
{
	return this->mContainerableView;
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
	this->mContainerableView->setX(this->getContentX());
	this->mContainerableView->setY(this->getContentY());

	this->mSpriteCredit.setPosition(this->getContainerableView()->getX(), 
									this->getContainerableView()->getY() + this->getContainerableView()->getHeight() + SPRITECREDIT_OFFSETY);

	this->mTBCredit.setPosition(this->getContainerableView()->getX() + this->mSpriteCredit.getLocalBounds().width + TEXTBOXCREDIT_OFFSETX,
								this->getContainerableView()->getY() + this->getContainerableView()->getHeight() + TEXTBOXCREDIT_OFFSETY);

	this->mButtonLootAll.setPosition(	this->getContainerableView()->getX() + this->getContainerableView()->getWidth() - this->mButtonLootAll.getWidth(),
										this->getContainerableView()->getY() + this->getContainerableView()->getHeight() + BUTTON_BOTTOM_OFFSETY);

	this->mButtonLootCredit.setPosition(this->mButtonLootAll.getX() - this->mButtonLootCredit.getWidth() - BUTTON_BOTTOM_OFFSETX,
										this->getContainerableView()->getY() + this->getContainerableView()->getHeight() + BUTTON_BOTTOM_OFFSETY);				
}

void WindowCargoLoot::notifyContainerableViewChanged()
{
	this->setContentHeight(this->mContainerableView->getHeight() + BOTTOM_HEIGHT);
	this->setContentWidth(this->mContainerableView->getWidth());
	this->notifyPositionChanged();
}

void WindowCargoLoot::notifyWreckChanged()
{
	if(this->getWreck() != NULL)
		this->mTBCredit.setText(Tools::formatNumber(this->getWreck()->getCredit()));

	this->getContainerableView()->setContainerable(this->getWreck());
}

void WindowCargoLoot::update()
{
	if(this->mContainerableView->isContainerableChanged())
		this->notifyContainerableViewChanged();

	if(this->isOpen() && !this->isReduce())
		this->mContainerableView->update();
}

void WindowCargoLoot::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonLootAll.update(p_event);
		this->mButtonLootCredit.update(p_event);
		this->mContainerableView->update(p_event);

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
		this->mContainerableView->draw();
		
		Resource::resource->getApp()->draw(this->mSpriteCredit);
		this->mTBCredit.draw();
		this->mButtonLootCredit.draw();
		this->mButtonLootAll.draw();
	}
}




