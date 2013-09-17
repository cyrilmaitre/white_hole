#include "StationScreenRightPanel.h"
#include "StationScreen.h"


//*************************************************************
// Define
//*************************************************************
#define PANEL_BACKCOLOR					sf::Color(128, 128, 128, 200)
#define PANEL_BORDCOLOR					sf::Color(128, 128, 128, 250)
#define PANEL_BORDSIZE					2
#define PANEL_PADDING					10


//*************************************************************
// Constructor - Destructor
//*************************************************************
StationScreenRightPanel::StationScreenRightPanel( Character* p_character, Station* p_station, StationScreen* p_screen )
{
	this->mCharacter = NULL;
	this->mStation = NULL;
	this->mStationScreen = NULL;

	this->setCharacter(p_character);
	this->setStation(p_station);
	this->setStationScreen(p_screen);

	this->setBorderSize(PANEL_BORDSIZE, true);
	this->setBorderColor(PANEL_BORDCOLOR, true);
	this->setBackgroundColor(PANEL_BACKCOLOR, true);
	this->setPadding(PANEL_PADDING);
	this->setDisplayTitle(false);
}

StationScreenRightPanel::~StationScreenRightPanel(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Character* StationScreenRightPanel::getCharacter()
{
	return this->mCharacter;
}

void StationScreenRightPanel::setCharacter( Character* p_character )
{
	if(this->mCharacter != p_character)
	{
		this->mCharacter = p_character;
		this->notifyCharacterChanged();
	}
}

Station* StationScreenRightPanel::getStation()
{
	return this->mStation;
}

void StationScreenRightPanel::setStation( Station* p_station )
{
	if(this->mStation != p_station)
	{
		this->mStation = p_station;
		this->notifyStationChanged();
	}
}

StationScreen* StationScreenRightPanel::getStationScreen()
{
	return this->mStationScreen;
}

void StationScreenRightPanel::setStationScreen( StationScreen* p_screen )
{
	this->mStationScreen = p_screen;
}


//*************************************************************
// Methods
//*************************************************************
void StationScreenRightPanel::update()
{
	
}

void StationScreenRightPanel::update( sf::Event p_event )
{
	FieldSet::update(p_event);
}

void StationScreenRightPanel::draw()
{
	FieldSet::draw();
}

void StationScreenRightPanel::unload()
{

}

void StationScreenRightPanel::notifyCharacterChanged()
{

}

void StationScreenRightPanel::notifyStationChanged()
{

}


