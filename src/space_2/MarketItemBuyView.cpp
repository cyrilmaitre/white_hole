#include "MarketItemBuyView.h"
#include "ContainerDropDown.h"
#include "Game.h"
#include "CharacterBank.h"
#include "Tools.h"


//*************************************************************
// Define
//*************************************************************
#define BACKGROUNDCOLOR						sf::Color(25, 26, 28)
#define BORDERCOLOR							sf::Color(255, 255, 255, 0)
#define BORDERSIZE							0
#define PADDING								10
#define TFQUANTITY_WIDTH					200
#define TFQUANTITY_MARGINTOP				10
#define BUTTONQUANTITYALL_MARGINLEFT		20
#define DESTINATION_MARGINTOP				35
#define DLLDESTINATION_MARGINTOP			10


//*************************************************************
// Constructor - Destructor
//*************************************************************
MarketItemBuyView::MarketItemBuyView(void)
{
	this->setVisible(false);
	this->setDisplayTitle(false);
	this->setBackgroundColor(BACKGROUNDCOLOR, true);
	this->setBorderColor(BORDERCOLOR, true);
	this->setBorderSize(BORDERSIZE, true);
	this->setPadding(PADDING);

	this->mTBQuantity.setText(Resource::resource->getBundle()->getString("marketBuyQuantity"));
	this->mTFQuantity.setValue("0");
	this->mTBDestination.setText(Resource::resource->getBundle()->getString("marketBuyToBank"));
	this->mButtonQuantityAll.setTitle(Resource::resource->getBundle()->getString("marketBuyQuantityAll"));

	this->updateDestinations();
}

MarketItemBuyView::~MarketItemBuyView(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
ItemStock* MarketItemBuyView::getItemStock()
{
	return this->mItemStock;
}

void MarketItemBuyView::setItemStock( ItemStock* p_stock )
{
	if(this->mItemStock != p_stock)
	{
		this->mItemStock = p_stock;
		this->notifyItemStockChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void MarketItemBuyView::update()
{
	this->checkQuantityValue();
	this->mDDLDestination.update();
}

void MarketItemBuyView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTFQuantity.update(p_event);
		this->mButtonQuantityAll.update(p_event);
		this->mDDLDestination.update(p_event);

		if(this->mButtonQuantityAll.isClicked())
		{
			if(this->mItemStock != NULL)
				this->mTFQuantity.setValue(Tools::buildStringWithLong(this->mItemStock->getStockCurrent()));
		}
	}
	FieldSet::update(p_event);
}

void MarketItemBuyView::updatePosition()
{
	this->mTBQuantity.setPosition(this->getContentX(), this->getContentY());
	this->mTFQuantity.setPosition(this->mTBQuantity.getX(), this->mTBQuantity.getBottomY() + TFQUANTITY_MARGINTOP);
	this->mButtonQuantityAll.setPosition(this->mTFQuantity.getRightX() + BUTTONQUANTITYALL_MARGINLEFT, this->mTFQuantity.getBottomY() - this->mButtonQuantityAll.getHeight());
	this->mTBDestination.setPosition(this->mTFQuantity.getX(), this->mTFQuantity.getBottomY() + DESTINATION_MARGINTOP);
	this->mDDLDestination.setPosition(this->mTBDestination.getX(), this->mTBDestination.getBottomY() + DLLDESTINATION_MARGINTOP);
}

void MarketItemBuyView::checkQuantityValue()
{
	if(this->mItemStock != NULL)
	{
		std::string quantityValue = this->mTFQuantity.getValue();
		if(!Tools::isNumber(quantityValue) && !quantityValue.empty())
		{
			this->mTFQuantity.setValue("0");
		}
		else
		{
			long quantity = Tools::getLongFromString(quantityValue);
			if(quantity < 0)
				quantity = 0;
			else if(quantity > this->mItemStock->getStockCurrent())
				quantity = this->mItemStock->getStockCurrent();

			this->mTFQuantity.setValue(Tools::buildStringWithLong(quantity));
		}
	}
}

void MarketItemBuyView::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBQuantity.draw();
		this->mTFQuantity.draw();
		this->mButtonQuantityAll.draw();
		this->mTBDestination.draw();
		this->mDDLDestination.draw();
	}
}

void MarketItemBuyView::notifyItemStockChanged()
{
	this->setVisible(this->mItemStock != NULL);
}

void MarketItemBuyView::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void MarketItemBuyView::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updatePosition();
}

void MarketItemBuyView::updateDestinations()
{
	Character* character = Game::game->getCharacter();

	this->mDDLDestination.removeAllDropDownable();
	this->mDDLDestination.addDropDownable(new ContainerDropDown(character->getShipPiloted()));
	for(int i = 0; i < character->getBankCount(); i++)
	{
		if(character->getBank(i)->isUnlock())
			this->mDDLDestination.addDropDownable(new ContainerDropDown(character->getBank(i)));
	}
}


