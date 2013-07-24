#include "WindowCargo.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowCargo::WindowCargo(void)
{
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(Resource::resource->getBundle()->getString("windowsTitleCargo"));
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_NINESQUARE));

	this->mContainerView = new ContainerView();
	this->notifyContainerViewChanged();
	
	this->setPositionMiddleScreen();
}

WindowCargo::~WindowCargo(void)
{
	delete this->mContainerView;
}

//*************************************************************
// Getters - Setterss
//*************************************************************
ContainerView* WindowCargo::getContainerView()
{
	return this->mContainerView;
}


//*************************************************************
// Methods
//*************************************************************
void WindowCargo::drawContent()
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerView->draw();
}

void WindowCargo::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->mContainerView->setX(this->getContentX());
	this->mContainerView->setY(this->getContentY());
}

void WindowCargo::update()
{
	if(this->mContainerView->isContainerableChanged())
		this->notifyContainerViewChanged();

	if(this->isOpen() && !this->isReduce())
		this->mContainerView->update();
}

void WindowCargo::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerView->update(p_event);
	Window::update(p_event);
}

void WindowCargo::notifyContainerViewChanged()
{
	this->setContentHeight(this->mContainerView->getHeight());
	this->setContentWidth(this->mContainerView->getWidth());
}
