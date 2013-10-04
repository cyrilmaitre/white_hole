#include "ContainerableView.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define CONTAINERVIEW_BOTTOM_HEIGHT		22
#define CONTAINERVIEW_BOTTOM_COLOR		sf::Color(100, 100, 100)
#define CONTAINERVIEW_TB_FONTCOLOR		sf::Color(255, 255, 255)
#define CONTAINERVIEW_TB_FONTSIZE		ManagerConfig::FontSize::Medium


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
ContainerableView::ContainerableView( double p_x, double p_y)
{
	this->mContainerable = NULL;
	this->mContainerableChanged = false;
	this->mDisplayEstimation = true;

	this->mBottomShape.setSize(sf::Vector2f(CONTAINERVIEW_ROW_WIDTH, CONTAINERVIEW_BOTTOM_HEIGHT));
	this->mBottomShape.setFillColor(CONTAINERVIEW_BOTTOM_COLOR);

	this->mTBEstimation.setFontColor(CONTAINERVIEW_TB_FONTCOLOR);
	this->mTBEstimation.setFontSize(CONTAINERVIEW_TB_FONTSIZE);

	this->setSize(CONTAINERVIEW_ROW_WIDTH, CONTAINERVIEW_ROW_HEIGHT);
	this->setBackgroundColor(CONTAINERVIEW_BACKGROUND_COLOR, true);
	this->setBorderColor(CONTAINERVIEW_BORDER_COLOR, true);
	this->setBorderSize(CONTAINERVIEW_BORDER_SIZE, true);
}

ContainerableView::~ContainerableView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Containerable* ContainerableView::getContainerable()
{
	return this->mContainerable;
}

void ContainerableView::setContainerable(Containerable* p_containerable)
{
	if(this->mContainerable != p_containerable)
	{
		this->mContainerable = p_containerable;
		this->notifyContainerableChanged();
	}
}

bool ContainerableView::isDisplayEstimation()
{
	return this->mDisplayEstimation;
}

void ContainerableView::setDisplayEstimation( bool p_estimation )
{
	if(this->mDisplayEstimation != p_estimation)
	{
		this->mDisplayEstimation = p_estimation;	
		this->updateHeight();
	}
}

bool ContainerableView::isContainerableChanged()
{
	bool returnValue = this->mContainerableChanged;
	this->mContainerableChanged = false;
	return returnValue;
}


//*************************************************************
// Methods
//*************************************************************
void ContainerableView::notifyContainerableChanged()
{
	this->clear();
	if(this->getContainerable() != NULL)
	{
		// Add RowView
		for(int i = 0; i < this->getContainerable()->getContainerRowCount(); i++)
		{
			this->addContainerRowView(new ContainerRowView(this->getContainerable()->getContainerRow(i)));
		}

		// Set other param
		this->updateHeight();
		this->updateEstimation();
		this->notifyPositionChanged();
		this->mContainerableChanged = true;
	}
}

void ContainerableView::updateHeight()
{
	if(this->isDisplayEstimation())
	{
		this->setHeight(this->getContainerable()->getContainerRowCount() * (CONTAINERVIEW_ROW_HEIGHT + CONTAINERVIEW_ROW_PADDING) + 
						CONTAINERVIEW_ROW_PADDINGTOP + 
						CONTAINERVIEW_BOTTOM_HEIGHT);
	}
	else
	{
		this->setHeight(this->getContainerable()->getContainerRowCount() * (CONTAINERVIEW_ROW_HEIGHT + CONTAINERVIEW_ROW_PADDING) + 
						CONTAINERVIEW_ROW_PADDINGTOP);
	}
}

void ContainerableView::notifyPositionChanged()
{
	Block::notifyPositionChanged();

	if(this->getContainerable() == NULL)
		return;

	for(int i = 0; i < this->mContainerRowViews.size(); i++)
	{
		this->mContainerRowViews[i]->updatePosition(this->getX() + CONTAINERVIEW_ROW_PADDINGLEFT, 
													this->getY() + CONTAINERVIEW_ROW_PADDINGTOP + i * (CONTAINERVIEW_ROW_HEIGHT + CONTAINERVIEW_ROW_PADDING));
	}
	
	this->mBottomShape.setPosition(this->getX(), this->getY() + this->getHeight() - CONTAINERVIEW_BOTTOM_HEIGHT);
	this->updateEstimationPosition();
}

void ContainerableView::updateEstimation()
{
	this->mTBEstimation.setText(Resource::resource->getBundle()->getString("windowCargoEstimation") + 
								Tools::getSpaceAfterColon() + 
								Tools::formatNumber((long)this->getContainerable()->getContentEstimation()));
	this->updateEstimationPosition();
}

void ContainerableView::updateEstimationPosition()
{
	this->mTBEstimation.setPosition(this->getX() + this->getWidth() - this->mTBEstimation.getWidth() - CONTAINERVIEW_ROW_PADDINGRIGHT,
									this->getY() + this->getHeight() - this->mTBEstimation.getHeight() - (CONTAINERVIEW_BOTTOM_HEIGHT - this->mTBEstimation.getHeight()) / 2);
}

void ContainerableView::update()
{
	if(this->getContainerable() == NULL)
		return;

	if(this->getContainerable()->isContentChanged())
		this->updateEstimation();

	for(int i = 0; i < this->mContainerRowViews.size(); i++)
	{
		this->mContainerRowViews[i]->update();
	}
}

void ContainerableView::update( sf::Event p_event )
{
	for(int i = 0; i < this->mContainerRowViews.size(); i++)
	{
		this->mContainerRowViews[i]->update(p_event);
	}

	Block::update(p_event);

	this->mTBEstimation.update(p_event);
}

void ContainerableView::draw()
{
	Block::draw();

	for(int i = 0; i < this->mContainerRowViews.size(); i++)
	{
		this->mContainerRowViews[i]->draw();
	}

	if(this->isDisplayEstimation())
	{
		Resource::resource->getApp()->draw(this->mBottomShape);
		this->mTBEstimation.draw();
	}
}

void ContainerableView::addContainerRowView( ContainerRowView* p_view )
{
	this->mContainerRowViews.push_back(p_view);
}

void ContainerableView::clear()
{
	for(int i = 0; i < this->mContainerRowViews.size(); i++)
	{
		this->mContainerRowViews[i]->clear();
		delete this->mContainerRowViews[i];
	}

	this->mContainerRowViews.clear();
}





