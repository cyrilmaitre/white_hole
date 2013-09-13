#include "StationScreenMarketBuy.h"
#include "FactoryGet.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR							sf::Color(255, 255, 255, 0)
#define PANEL_BORDCOLOR							sf::Color(194, 194, 194)
#define PANEL_BORDSIZE							2
#define PANEL_TREEITEMTYPE_WIDTH				250
#define PANEL_ITEMLIST_PADDING					0
#define PANEL_ITEMLIST_BACKCOLOR				sf::Color(25, 26, 28)
#define PANEL_ITEMLIST_SEPARATOR_HEIGHT			1
#define PANEL_ITEMLIST_SEPARATOR_COLOR			sf::Color(86, 87, 89)


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
void StationScreenMarketBuy::update()
{
	if(this->mTreeItemType.isSelectedChanged())
		this->notifyItemTypeSelectedChanged();
}

void StationScreenMarketBuy::updatePosition()
{
	this->mTreeItemType.setPosition(this->getContentX(), this->getContentY());
	this->mItemList.setPosition(this->mTreeItemType.getRightX(), this->getContentY());
}

void StationScreenMarketBuy::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mTreeItemType.update(p_event);
		this->mItemList.update(p_event);
	}
	FieldSet::update(p_event);
}

void StationScreenMarketBuy::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mTreeItemType.draw();
		this->mItemList.draw();
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
	this->mTreeItemType.setHeight(this->getContentHeight());
	this->mItemList.setHeight(this->getContentHeight());
}

void StationScreenMarketBuy::notifyItemTypeSelectedChanged()
{
	// Get ItemType Selected
	Node* selectedNode = dynamic_cast<Node*>(this->mTreeItemType.getSelected());
	ItemType* selectedItemType = NULL;
	if(selectedNode != NULL)
		selectedItemType = dynamic_cast<ItemType*>(selectedNode->getNodeData());

	// If not NULL -> populate Item list
	if(selectedItemType != NULL)
	{
		this->mItemList.clear();
		for(int i = 0; i < selectedItemType->getItemCount(); i++)
		{
			MarketItemListView* newView = new MarketItemListView(selectedItemType->getItem(i));
			this->mItemList.addItem(newView, false);
		}
		this->mItemList.notifyDataSetChanged();
	}
}
