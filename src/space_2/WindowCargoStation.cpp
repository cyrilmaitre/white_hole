#include "WindowCargoStation.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowCargoStation::WindowCargoStation(std::string p_title, ContainerableView* p_containerableView)
{
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(p_title);
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_NINESQUARE));

	if(p_containerableView != NULL)
	{
		this->mContainerViewDeletion = false;
		this->mContainerView = p_containerableView;
	}
	else
	{
		this->mContainerViewDeletion = true;
		this->mContainerView = new ContainerableView();
	}
	this->notifyContainerableViewChanged();

	this->setPositionMiddleScreen();
}

WindowCargoStation::~WindowCargoStation(void)
{
	if(this->mContainerViewDeletion)
		delete this->mContainerView;
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerableView* WindowCargoStation::getContainerableView()
{
	return this->mContainerView;
}


//*************************************************************
// Methods
//*************************************************************
void WindowCargoStation::drawContent()
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerView->draw();
}

void WindowCargoStation::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->mContainerView->setX(this->getContentX());
	this->mContainerView->setY(this->getContentY());
}

void WindowCargoStation::update()
{
	if(this->mContainerView->isContainerableChanged())
		this->notifyContainerableViewChanged();

	if(this->isOpen() && !this->isReduce())
		this->mContainerView->update();
}

void WindowCargoStation::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerView->update(p_event);
	Window::update(p_event);
}

void WindowCargoStation::notifyContainerableViewChanged()
{
	this->setContentHeight(this->mContainerView->getHeight());
	this->setContentWidth(this->mContainerView->getWidth());
}
