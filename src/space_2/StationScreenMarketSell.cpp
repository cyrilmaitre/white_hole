#include "StationScreenMarketSell.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR					sf::Color(25, 26, 28)
#define PANEL_BORDCOLOR					sf::Color(194, 194, 194)
#define PANEL_BORDSIZE					2
#define CARGOMAX						64
#define CONTAINER_MARGINBOTTOM			20
#define TBTOTALLABEL_MARGINBOTTOM		10
#define TBTOTAL_FONTSIZE				22
#define BUTTONBUY_MARGINTOP				40
#define DETAIL_MARGIN_LEFT				20
#define DETAIL_WIDTH					400
#define DETAIL_BORDERSIZE				1
#define DETAIL_BORDERCOLOR				sf::Color(125, 125, 125)


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenMarketSell::StationScreenMarketSell( StationScreenMarket* p_market )
{
	this->mScreenMarket = p_market;
	
	this->setBackgroundColor(PANEL_BACKCOLOR, true);
	this->setBorderColor(PANEL_BORDCOLOR, true);
	this->setBorderSize(PANEL_BORDSIZE, true);
	this->setDisplayTitle(false);

	this->setCargoMax(CARGOMAX);
	this->setType(ContainerStack::ContainerStackType::TypeNone);
	this->mContainerView.setContainerable(this);
	this->mContainerView.setDisplayEstimation(false);

	this->mTBTotalLabel.setFontSize(TBTOTAL_FONTSIZE);
	this->mTBTotalLabel.setText(Resource::resource->getBundle()->getString("totalMaj"));
	this->mTBTotal.setFontSize(TBTOTAL_FONTSIZE);
	this->mButtonSell.setTitle(Resource::resource->getBundle()->getString("sell"));

	this->mTBMLDetail.setSize(DETAIL_WIDTH, this->mContainerView.getHeight());
	this->mTBMLDetail.setBorderColor(DETAIL_BORDERCOLOR, true);
	this->mTBMLDetail.setBorderSize(DETAIL_BORDERSIZE, true);
	this->mTBMLDetail.setForceScrollBar(true);
}

StationScreenMarketSell::~StationScreenMarketSell(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenMarketSell::update()
{
	if(this->isVisible())
	{
		this->mContainerView.update();
	}
}

void StationScreenMarketSell::updatePosition()
{
	this->mContainerView.setPosition(this->getContentX(), this->getContentY());
	this->mTBTotalLabel.setPosition(this->getContentX() + (this->mContainerView.getWidth() - this->mTBTotalLabel.getWidth()) / 2, this->mContainerView.getBottomY() + CONTAINER_MARGINBOTTOM);
	this->mTBTotal.setPosition(this->getContentX() + (this->mContainerView.getWidth() - this->mTBTotal.getWidth()) / 2, this->mTBTotalLabel.getBottomY() + TBTOTALLABEL_MARGINBOTTOM);
	this->mButtonSell.setPosition(this->getContentX() + (this->mContainerView.getWidth() - this->mButtonSell.getWidth()) / 2, this->mTBTotal.getBottomY() + BUTTONBUY_MARGINTOP);
	this->mTBMLDetail.setPosition(this->mContainerView.getRightX() + DETAIL_MARGIN_LEFT, this->getContentY());
}

void StationScreenMarketSell::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mContainerView.update(p_event);
		this->mButtonSell.update(p_event);
		this->mTBMLDetail.update(p_event);
	}
	FieldSet::update(p_event);
}

void StationScreenMarketSell::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mContainerView.draw();
		this->mTBTotalLabel.draw();
		this->mTBTotal.draw();
		this->mButtonSell.draw();
		this->mTBMLDetail.draw();
	}
}

void StationScreenMarketSell::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}
