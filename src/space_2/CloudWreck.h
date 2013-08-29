#pragma once
#include "MapObject.h"
#include "CloudWreckModel.h"

class CloudWreck : public MapObject
{
public:
	// Constructor - Destructor
	CloudWreck(void);
	~CloudWreck(void);

	// Getters - Setters
	CloudWreckModel* getCloudModel();
	void setCloudModel(CloudWreckModel* p_model);

	// Methods
	void update();
	void notifyCloudModelChanged();
	void loadSprite();


private:
	// Attributs
	CloudWreckModel* mCloudModel;
};

