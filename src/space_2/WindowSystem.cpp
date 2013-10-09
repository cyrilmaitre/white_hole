#include "WindowSystem.h"
#include "Game.h";


//*************************************************************
// Define
//*************************************************************
#define WINDOW_HEIGHT				250
#define BUTTON_MARGINTOP			10


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSystem::WindowSystem(void)
{
	this->setContentWidth(this->mButtonOption.getWidth());
	this->setContentHeight(WINDOW_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(Resource::resource->getBundle()->getString("system"));
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));

	this->mButtonOption.setTitle(Resource::resource->getBundle()->getString("options"));
	this->mButtonLogout.setTitle(Resource::resource->getBundle()->getString("logout"));
	this->mButtonQuit.setTitle(Resource::resource->getBundle()->getString("quit"));	

	this->setPositionMiddleScreen();
}

WindowSystem::~WindowSystem(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void WindowSystem::updatePosition()
{
	this->mButtonOption.setPosition(this->getContentX(), this->getContentY());
	this->mButtonLogout.setPosition(this->getContentX(), this->mButtonOption.getBottomY() + BUTTON_MARGINTOP);
	this->mButtonQuit.setPosition(this->getContentX(), this->getContentY() + this->getContentHeight() - this->mButtonQuit.getHeight());
}

void WindowSystem::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonOption.update(p_event);

		this->mButtonLogout.update(p_event);
		if(this->mButtonLogout.isClicked())
			Game::game->setRunning(false);

		this->mButtonQuit.update(p_event);
		if(this->mButtonQuit.isClicked())
			Resource::resource->setAppRunning(false);
	}
	Window::update(p_event);
}

void WindowSystem::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonOption.draw();
		this->mButtonLogout.draw();
		this->mButtonQuit.draw();
	}
}

void WindowSystem::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->updatePosition();
}
