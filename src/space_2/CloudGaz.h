#pragma once
#include "MapObject.h"
#include "CloudGazModel.h"

// TODO: Remove mSize and his getter / setters
class CloudGaz : public MapObject
{
public:
	// Constructor - Destructor
	CloudGaz(void);
	~CloudGaz(void);

	// Getters - Setters
	CloudGazModel* getCloudModel();
	void setCloudModel(CloudGazModel* p_model);
	
	sf::Color getCloudColor();
	void setCloudColor(sf::Color p_color);

	// Methods
	void notifyCloudModelChanged();
	void notifyCloudColorChanged();
	void loadSprite();


private:
	// Attributs
	CloudGazModel* mCloudModel;
	sf::Color mCloudColor;
};

