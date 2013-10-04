#include "ContainerView.h"
#include "ContainerViewManager.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERVIEW_HEIGHT_DRAG					36
#define CONTAINERVIEW_BACKGROUNDICON_COLOR			sf::Color(55, 55, 55)
#define BACKGROUNDICON_OFFSETX						2
#define BACKGROUNDICON_OFFSETY						2


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerView::ContainerView(void)
{
	this->mIcon = NULL;

	this->setSize(CONTAINERVIEW_WIDTH, CONTAINERVIEW_HEIGHT_DRAG);

	this->mBackground.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	this->mBackground.setFillColor(CONTAINERVIEW_BACKGROUND_COLOR);

	this->mBackgroundIcon.setSize(sf::Vector2f(CONTAINERVIEW_BACKGROUNDICON_WIDTH, CONTAINERVIEW_BACKGROUNDICON_HEIGHT));
	this->mBackgroundIcon.setFillColor(CONTAINERVIEW_BACKGROUNDICON_COLOR);
}

ContainerView::~ContainerView(void)
{
	this->deleteIcon();
}

void ContainerView::deleteIcon()
{
	if(this->mIcon != NULL)
		delete this->mIcon;
	this->mIcon = NULL;
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::Sprite* ContainerView::getIcon()
{
	return this->mIcon;
}

ContainerView::ContainerViewType ContainerView::getContainerViewType()
{
	return this->mContainerViewType;
}

void ContainerView::setContainerViewType( ContainerViewType p_type )
{
	this->mContainerViewType = p_type;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerView::update()
{
	
}

void ContainerView::update( sf::Event p_event )
{
	Focusable::update(p_event);
}

void ContainerView::updatePosition()
{
	this->mBackground.setPosition(this->getX(), this->getY());
	this->mBackgroundIcon.setPosition(this->getX() + BACKGROUNDICON_OFFSETX, this->getY() + BACKGROUNDICON_OFFSETY);

	if(this->mIcon != NULL)
		this->mIcon->setPosition(this->getX() + BACKGROUNDICON_OFFSETX, this->getY() + BACKGROUNDICON_OFFSETY);
}

void ContainerView::draw()
{
	Resource::resource->getApp()->draw(this->mBackground);
	Resource::resource->getApp()->draw(this->mBackgroundIcon);

	if(this->mIcon != NULL)
		Resource::resource->getApp()->draw(*this->mIcon);
}

void ContainerView::notifyPositionChanged()
{
	Focusable::notifyPositionChanged();
	this->updatePosition();
}
