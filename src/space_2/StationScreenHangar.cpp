#include "StationScreenHangar.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
#define SHIPLIST_HEIGHT					500
#define SHIPLIST_BACKGROUNDCOLOR		sf::Color(25, 26, 28)
#define	SHIPLIST_BORDERCOLOR			sf::Color(194, 194, 194)
#define SHIPLIST_BORDERSIZE				1
#define SHIPLIST_SEPARATORSIZE			1
#define SHIPLIST_SEPARATORCOLOR			sf::Color(86, 87, 89)
#define SHIPLIST_PADDING				0


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenHangar::StationScreenHangar( Character* p_character, Station* p_station, StationScreen* p_screen ) : StationScreenRightPanel(p_character, p_station, p_screen)
{
	this->setTitle(Resource::resource->getBundle()->getString("hangar"));
	this->setDisplayTitle(true);

	this->mShipList.setSize(HANGARSHIPLISTVIEW_WIDTH + SCROLLBAR_WIDTH + SHIPLIST_PADDING * 2, SHIPLIST_HEIGHT);
	this->mShipList.setBackgroundColor(SHIPLIST_BACKGROUNDCOLOR, true);
	this->mShipList.setBorderColor(SHIPLIST_BORDERCOLOR, true);
	this->mShipList.setBorderSize(SHIPLIST_BORDERSIZE, true);
	this->mShipList.setSeparatorColor(SHIPLIST_SEPARATORCOLOR);
	this->mShipList.setSeparatorHeight(SHIPLIST_SEPARATORSIZE);
	this->mShipList.setForceScrollBar(true);
}

StationScreenHangar::~StationScreenHangar(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenHangar::load()
{
	this->mShipList.clear(false);
	if(this->getCharacter() != NULL)
	{
		for(int i = 0; i < this->getCharacter()->getShipCount(); i++)
		{
			HangarShipListView* newShipView = new HangarShipListView(this->getCharacter()->getShip(i));
			this->mShipList.addItem(newShipView, false);
		}
	}
	this->mShipList.notifyDataSetChanged();
}

void StationScreenHangar::unload()
{
	this->mShipList.clear();
}

void StationScreenHangar::update()
{

}

void StationScreenHangar::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		this->mShipList.update(p_event);
	}
	FieldSet::update(p_event);
}

void StationScreenHangar::updatePosition()
{
	this->mShipList.setPosition(this->getContentX(), this->getContentY());
}

void StationScreenHangar::draw()
{
	FieldSet::draw();
	if(this->isVisible())
	{
		this->mShipList.draw();
	}
}

void StationScreenHangar::notifySizeChanged()
{
	FieldSet::notifySizeChanged();
}

void StationScreenHangar::notifyPositionChanged()
{
	FieldSet::notifyPositionChanged();
	this->updatePosition();
}
