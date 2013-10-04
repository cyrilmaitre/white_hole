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

	this->mContainerableView = new ContainerableView();
	this->notifyContainerableViewChanged();
	
	this->setPositionMiddleScreen();
}

WindowCargo::~WindowCargo(void)
{
	delete this->mContainerableView;
}

//*************************************************************
// Getters - Setterss
//*************************************************************
ContainerableView* WindowCargo::getContainerableView()
{
	return this->mContainerableView;
}


//*************************************************************
// Methods
//*************************************************************
void WindowCargo::drawContent()
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerableView->draw();
}

void WindowCargo::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->mContainerableView->setX(this->getContentX());
	this->mContainerableView->setY(this->getContentY());
}

void WindowCargo::update()
{
	if(this->mContainerableView->isContainerableChanged())
		this->notifyContainerableViewChanged();

	if(this->isOpen() && !this->isReduce())
		this->mContainerableView->update();
}

void WindowCargo::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
		this->mContainerableView->update(p_event);
	Window::update(p_event);
}

void WindowCargo::notifyContainerableViewChanged()
{
	this->setContentHeight(this->mContainerableView->getHeight());
	this->setContentWidth(this->mContainerableView->getWidth());
}
