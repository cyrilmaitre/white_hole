#include "ContainerRowView.h"
#include "ContainerView.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
ContainerRowView::ContainerRowView(ContainerRow* p_row) 
{
	this->setSize(CONTAINERROWVIEW_WIDTH, CONTAINERROWVIEW_HEIGHT);
	this->setContainerRow(p_row);
}

ContainerRowView::~ContainerRowView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ContainerRow* ContainerRowView::getContainerRow()
{
	return this->mContainerRow;
}

void ContainerRowView::setContainerRow( ContainerRow* p_row )
{
	this->mContainerRow = p_row;
	this->notifyContainerRowChanged();
}


//*************************************************************
// Methods
//*************************************************************
void ContainerRowView::update()
{
	for(int i = 0; i < this->mContainerStackViews.size(); i++)
	{
		this->mContainerStackViews[i]->update();
	}
}

void ContainerRowView::updatePosition( double newX, double newY )
{
	this->setPosition(newX, newY);

	for(int i = 0; i < this->mContainerStackViews.size(); i++)
	{
		this->mContainerStackViews[i]->updatePosition(	this->getX() + (CONTAINERSTACKVIEW_WIDTH + CONTAINERSTACKVIEW_PADDING) * i,
														this->getY());
	}
}

void ContainerRowView::update( sf::Event p_event )
{
	for(int i = 0; i < this->mContainerStackViews.size(); i++)
	{
		this->mContainerStackViews[i]->update(p_event);
	}
}

void ContainerRowView::draw()
{
	for(int i = 0; i < this->mContainerStackViews.size(); i++)
	{
		this->mContainerStackViews[i]->draw();
	}
}

void ContainerRowView::addContainerStackView( ContainerStackView* p_view )
{
	this->mContainerStackViews.push_back(p_view);
}

void ContainerRowView::notifyContainerRowChanged()
{
	this->clear();
	if(this->getContainerRow() != NULL)
	{
		// Add StackView
		for(int i = 0; i < this->getContainerRow()->getContainerStacksCount(); i++)
		{
			this->addContainerStackView(new ContainerStackView(this->getContainerRow()->getContainerStack(i)));
		}
	}
}

void ContainerRowView::clear()
{
	for(int i = 0; i < this->mContainerStackViews.size(); i++)
	{
		delete this->mContainerStackViews[i];
	}

	this->mContainerStackViews.clear();
}
