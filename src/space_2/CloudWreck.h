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

	float getRotationSpeed();
	void setRotationSpeed(float p_speed);

	bool getRotationDirection();
	void setRotationDirection(bool p_direction);

	// Methods
	void update();
	void notifyCloudModelChanged();
	void notifyRotationChanged();
	void loadSprite();


private:
	// Attributs
	CloudWreckModel* mCloudModel;
	float mRotationSpeed;
	bool mRotationDirection;
	mks::Clock mRotationClock;
};

