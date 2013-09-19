#include "StationScreenMarketBuy.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR							sf::Color(25, 26, 28)
#define PANEL_BORDCOLOR							sf::Color(194, 194, 194)
#define PANEL_BORDSIZE							2
#define PANEL_TREEITEMTYPE_WIDTH				250
#define PANEL_ITEMLIST_PADDING					0
#define PANEL_ITEMLIST_BACKCOLOR				sf::Color(25, 26, 28)
#define PANEL_ITEMLIST_SEPARATOR_HEIGHT			1
#define PANEL_ITEMLIST_SEPARATOR_COLOR			sf::Color(86, 87, 89)
#define PANEL_SELECTITEM_FONTSIZE				20
#define PANEL_ITEMSTOCK_MARGIN					10


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenMarketBuy::StationScreenMarketBuy( StationScreenMarket* p_market ) : mItemList(true)
{
	this->mScreenMarket = p_market;

	this->setBackgroundColor(PANEL_BACKCOLOR, true);
	this->setBorderColor(PANEL_BORDCOLOR, true);
	this->setBorderSize(PANEL_BORDSIZE, true);
	this->setDisplayTitle(false);
	this->setPadding(0);

	this->mTBSelectItem.setText(Resource::resource->getBundle()->getString("marketBuySelectItem"));
	this->mTBSelectItem.setFontSize(PANEL_SELECTITEM_FONTSIZE);

	this->mTreeItemType.setSize(PANEL_TREEITEMTYPE_WIDTH, this->getContentHeight());
	this->mTreeItemType.setBorderColor(sf::Color(255, 255, 255, 0), true);
	this->mTreeItemType.setBorderSize(0, true);
	this->mTreeItemType.setTreeData(FactoryGet::getItemTypeFactory()->getItemTypeTree());

	this->mItemList.setSize(MARKETITEMLISTVIEW_WIDTH + SCROLLBAR_WIDTH + PANEL_ITEMLIST_PADDING * 2, this->getContentHeight());
	this->mItemList.setBackgroundColor(PANEL_ITEMLIST_BACKCOLOR, true);
	this->mItemList.setBorderColor(sf::Color(255, 255, 255, 0), true);
	this->mItemList.setBorderSize(0, true);
	this->mItemList.setPadding(PANEL_ITEMLIST_PADDING);
	this->mItemList.setSeparatorHeight(PANEL_ITEMLIST_SEPARATOR_HEIGHT);
	this->mItemList.setSeparatorColor(PANEL_ITEMLIST_SEPARATOR_COLOR);
	this->mItemList.setForceScrollBar(true);
}

StationScreenMarketBuy::~StationScreenMarketBuy(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
void StationScreenMarketBuy::reset()
{
	this->mItemList.unselectAll();
}

void StationScreenMarketBuy::update()
{
	if(this->mTreeItemType.isSelectionChanged())
		this->notifyItemTypeSelectedChanged();

	if(this->mItemList.isSelectionChanged())
		this->notifyItemSelectedChanged();

	this->mItemStock.update();
	this->mItemBuy.update();
}

void StationScreenMarketBuy::updatePosition()
{
	this->mTreeItemType.setPosition(this->getContentX(), this->getContentY());
	this->mItemList.setPosition(this->mTreeItemType.getRightX(), this->getContentY());
	this->mTBSelectItem.setPosition(this->mItemList.getRightX() + (this->getWidth() - this->mTreeItemType.getWidth() - this->mItemList.getWidth() - this->mTBSelectItem.getWidth()) / 2, 
									this->getY() + (this->getHeight() - this->mTBSelectItem.getHeight()) / 2);
	this->mItemDetail.setPosition(this->mItemList.getRightX(), this->getContentY());
	this->mItemStock.setPosition(this->mItemList.getRightX() + PANEL_ITEMSTOCK_MARGIN, this->mItemDetail.getBottomY() + PANEL_ITEMSTOCK_MARGIN);
	this->mItemBuy.setPosition(this->mItemList.getRightX(), this->mItemStock.getBottomY() + PANEL_ITEMSTOCK_MARGIN);
}

void StationScreenMarketBuy::updateSize()
{
	this->mTreeItemType.setHeight(this->getContentHeight());
	this->mItemList.setHeight(this->getContentHeight());
	this->mItemDetail.setWidth(this->getContentWidth() - this->mTreeItemType.getWidth() - this->mItemList.getWidth());
	this->mItemStock.setWidth(this->mItemDetail.getWidth() - PANEL_ITEMSTOCK_MARGIN * 2);
	this->mItemBuy.setSize(this->mItemDetail.getWidth(), this->getContentHeight() - this->mItemDetail.getHeight() - this->mItemStock.getHeight() - PANEL_ITEMSTOCK_MARGIN * 2);
}

void StationScreenMarketBuy::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTreeItemType.update(p_event);
		this->mItemList.update(p_event);
		this->mItemDetail.update(p_event);
		this->mItemStock.update(p_event);
		this->mItemBuy.update(p_event);
	}
	FieldSet::update(p_event);
}

void StationScreenMarketBuy::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTBSelectItem.draw();
		this->mTreeItemType.draw();
		this->mItemList.draw();
		this->mItemDetail.draw();
		this->mItemStock.draw();
		this->mItemBuy.draw();
	}
}

void StationScreenMarketBuy::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}

void StationScreenMarketBuy::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
	this->updateSize();
	this->updatePosition();
}

void StationScreenMarketBuy::notifyItemTypeSelectedChanged()
{
	// Get ItemType Selected
	Node* selectedNode = dynamic_cast<Node*>(this->mTreeItemType.getSelection());
	ItemType* selectedItemType = NULL;
	if(selectedNode != NULL)
		selectedItemType = dynamic_cast<ItemType*>(selectedNode->getNodeData());

	// If not NULL -> populate Item list
	if(selectedItemType != NULL)
	{
		this->mItemList.clear();
		for(int i = 0; i < selectedItemType->getItemCount(); i++)
		{
			Item* currentItem = selectedItemType->getItem(i);
			if(currentItem->isBuyable())
			{
				MarketItemListView* newView = new MarketItemListView(currentItem);
				this->mItemList.addItem(newView, false);
			}
		}
		this->mItemList.notifyDataSetChanged();
	}
}

void StationScreenMarketBuy::notifyItemSelectedChanged()
{
	MarketItemListView* selectedItemView = dynamic_cast<MarketItemListView*>(this->mItemList.getSelection());
	if(selectedItemView != NULL)
	{
		Item* selectedItem = selectedItemView->getItem();
		this->mItemDetail.setItem(selectedItem);

		ItemStock* selectedItemStock = this->mScreenMarket->getStation()->getItemStock(selectedItem); 
		this->mItemStock.setItemStock(selectedItemStock);		
		this->mItemBuy.setItemStock(selectedItemStock);
	}
	else
	{
		this->mItemDetail.setItem(NULL);
		this->mItemStock.setItemStock(NULL);	
		this->mItemBuy.setItemStock(NULL);
	}
	this->mTBSelectItem.setVisible(selectedItemView == NULL);
	this->updateSize();
	this->updatePosition();
}
