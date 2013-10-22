#include "StationScreenMarketSell.h"
#include "ItemStockSimulator.h"
#include "UserInterface.h"
#include "WindowChoiceAsk.h"
#include "WindowMessageSuccess.h"
#include "Game.h"
#include "Jukebox.h"


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
#define DETAIL_PADDING					5
#define UPDATE_TICK						500	// ms
#define ACTIONCOMMAND_SELL				"actioncommand_sell"
#define SOUND_MONEY						"windowPurchase.ogg"


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
	this->setType(Containerable::ContainerStackType::TypeNone);
	this->mContainerableView.setContainerable(this);
	this->mContainerableView.setDisplayEstimation(false);

	this->mTBTotalLabel.setFontSize(TBTOTAL_FONTSIZE);
	this->mTBTotalLabel.setText(Resource::resource->getBundle()->getString("totalMaj"));
	this->mTBTotal.setFontSize(TBTOTAL_FONTSIZE);
	this->mButtonSell.setTitle(Resource::resource->getBundle()->getString("sell"));

	this->mTBMLDetail.setSize(DETAIL_WIDTH, this->mContainerableView.getHeight());
	this->mTBMLDetail.setBorderColor(DETAIL_BORDERCOLOR, true);
	this->mTBMLDetail.setBorderSize(DETAIL_BORDERSIZE, true);
	this->mTBMLDetail.setForceScrollBar(true);
	this->mTBMLDetail.setPadding(DETAIL_PADDING);

	this->updateItemsCount();
}

StationScreenMarketSell::~StationScreenMarketSell(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenMarketSell::sell()
{
	// Check price & Inc stock
	double totalPrice = 0;
	ItemStockSimulator stockSimulator;
	std::map<Item*, int>::iterator iter;
	for (iter = this->mContainerItemsCount.begin(); iter != this->mContainerItemsCount.end(); ++iter)
	{
		// Price
		stockSimulator.setItemStock(this->mScreenMarket->getStation()->getItemStock(iter->first));
		stockSimulator.computeSellPrice(iter->second);
		totalPrice += stockSimulator.getSellPrice();

		// Inc stock
		this->mScreenMarket->getStation()->getItemStock(iter->first)->incStockCurrent(iter->second);
	}

	// Inc credit
	double oldBalance = Game::game->getCharacter()->getCredit();
	Game::game->getCharacter()->incCredit(totalPrice);
	double newBalance = Game::game->getCharacter()->getCredit();

	// Empty container
	this->mContainerableView.getContainerable()->empty();

	// Message success
	std::string messageSuccess = Resource::resource->getBundle()->getString("marketSellSuccessMsg1") + "<br/>";
	messageSuccess += Resource::resource->getBundle()->getString("marketSellSuccessMsg2") + Tools::getSpaceAfterColon() + Tools::formatNumber(totalPrice) + "<br/>";
	messageSuccess += Resource::resource->getBundle()->getString("marketSellSuccessMsg3") + Tools::getSpaceAfterColon() + Tools::formatNumber(oldBalance) + "<br/>";
	messageSuccess += Resource::resource->getBundle()->getString("marketSellSuccessMsg4") + Tools::getSpaceAfterColon() + Tools::formatNumber(newBalance);
	UserInterface::mUserInterface->addWindowPopup(new WindowMessageSuccess(Resource::resource->getBundle()->getString("marketSellSuccessTitle"), messageSuccess));
	Jukebox::getInstance()->playSound(SOUND_MONEY);
}

void StationScreenMarketSell::sellConfirmation()
{
	std::string messageConfirmation = Resource::resource->getBundle()->getString("marketSellConfirmationMsg1") + "<br/>";

	double totalPrice = 0;
	ItemStockSimulator stockSimulator;
	std::map<Item*, int>::iterator iter;
	for (iter = this->mContainerItemsCount.begin(); iter != this->mContainerItemsCount.end(); ++iter)
	{
		stockSimulator.setItemStock(this->mScreenMarket->getStation()->getItemStock(iter->first));
		stockSimulator.computeSellPrice(iter->second);
		totalPrice += stockSimulator.getSellPrice();

		messageConfirmation += "- " + iter->first->getName() + " (x" + Tools::formatNumber(iter->second) + ")<br/>";
	}

	messageConfirmation += "  <br/>" + Resource::resource->getBundle()->getString("marketSellConfirmationMsg2");
	messageConfirmation += " " + Tools::formatNumber(totalPrice) + " ";
	messageConfirmation += Resource::resource->getBundle()->getString("marketSellConfirmationMsg3");

	UserInterface::mUserInterface->addWindowPopup(new WindowChoiceAsk(	Resource::resource->getBundle()->getString("marketBuyConfirmationTitle"), 
																		messageConfirmation, this, NULL, ACTIONCOMMAND_SELL));
}

void StationScreenMarketSell::update()
{
	if(this->isVisible())
	{
		if(this->mContainerableView.getContainerable()->isContentChanged(false))
			this->updateItemsCount();

		this->mContainerableView.update();

		if(this->mTotalClock.getElapsedTimeAsMilliseconds() > UPDATE_TICK)
		{
			this->updateTotal();	
			this->mTotalClock.restart();
		}
	}
}

void StationScreenMarketSell::updatePosition()
{
	this->mContainerableView.setPosition(this->getContentX(), this->getContentY());
	this->mTBTotalLabel.setPosition(this->getContentX() + (this->mContainerableView.getWidth() - this->mTBTotalLabel.getWidth()) / 2, this->mContainerableView.getBottomY() + CONTAINER_MARGINBOTTOM);
	this->updateTotalPosition();
	this->mButtonSell.setPosition(this->getContentX() + (this->mContainerableView.getWidth() - this->mButtonSell.getWidth()) / 2, this->mTBTotal.getBottomY() + BUTTONBUY_MARGINTOP);
	this->mTBMLDetail.setPosition(this->mContainerableView.getRightX() + DETAIL_MARGIN_LEFT, this->getContentY());
}

void StationScreenMarketSell::updateTotalPosition()
{
	this->mTBTotal.setPosition(this->getContentX() + (this->mContainerableView.getWidth() - this->mTBTotal.getWidth()) / 2, this->mTBTotalLabel.getBottomY() + TBTOTALLABEL_MARGINBOTTOM);
}

void StationScreenMarketSell::updateTotal()
{
	double totalPrice = 0;
	ItemStockSimulator stockSimulator;

	std::map<Item*, int>::iterator iter;
	this->mTBMLDetail.clear(true);
	for (iter = this->mContainerItemsCount.begin(); iter != this->mContainerItemsCount.end(); ++iter)
	{
		stockSimulator.setItemStock(this->mScreenMarket->getStation()->getItemStock(iter->first));
		stockSimulator.computeSellPrice(iter->second);
		totalPrice += stockSimulator.getSellPrice();

		this->mTBMLDetail.addLine(iter->first->getName() + " (x" + Tools::formatNumber(iter->second) + "):" + Tools::getSpaceAfterColon() + Tools::formatNumber(stockSimulator.getSellPrice()) + " " + Resource::resource->getBundle()->getString("creditAb"));
		this->mTBMLDetail.addLine("        " + Resource::resource->getBundle()->getString("marketSellAverage") + Tools::getSpaceAfterColon() + Tools::formatNumber(stockSimulator.getSellPriceAve()) + " " + Resource::resource->getBundle()->getString("creditAb"));
	}
	this->mTBTotal.setText(Tools::formatNumber(totalPrice) + " " + Resource::resource->getBundle()->getString("creditAb"));
	this->updateTotalPosition();
}

void StationScreenMarketSell::updateItemsCount()
{
	this->mContainerItemsCount = this->mContainerableView.getContainerable()->getItemsCount();
	this->mTBMLDetail.setVisible(this->mContainerItemsCount.size() > 0);
	this->mButtonSell.setEnable(this->mContainerItemsCount.size() > 0);
	this->updateTotal();
}

void StationScreenMarketSell::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mContainerableView.update(p_event);
		this->mButtonSell.update(p_event);
		this->mTBMLDetail.update(p_event);

		if(this->mButtonSell.isClicked())
			this->sellConfirmation();
	}
	FieldSet::update(p_event);
}

void StationScreenMarketSell::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mContainerableView.draw();
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

void StationScreenMarketSell::onButtonTrueClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{
	this->sell();
}

void StationScreenMarketSell::onButtonFalseClicked( WindowChoiceActionObject* p_object, std::string p_actionCommand )
{

}


