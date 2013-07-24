#pragma once
#include "Resource.h"
#include "MapObject.h"
#include "SelectableGroup.h"

class MapObjectSelector
{
public:
	// Constructor - Destructor
	MapObjectSelector(void);
	~MapObjectSelector(void);

	// Getters - Setters
	MapObject* getSelectedMapObject();

	double getObjectSelectedDistance();
	void setObjectSelectedDistance(double p_distance);

	float getObjectSelectedAngle();
	void setObjectSelectedAngle(float p_angle);

	bool hasObjectSelected();
	bool isObjectSelectedOutOfScreen();

	// Methods
	void update();
	void unselect();
	void addMapObject(MapObject* p_object);
	void removeMapObject(MapObject* p_object);	


private:
	// Attributes
	SelectableGroup mMapObjectSelectable;
	double mObjectSelectedDistance;
	float mObjectSelectedAngle;
	bool mObjectSelectedOutOfScreen;

	// Methods
	void updateDistance();
	void updateAngle();
	void updateOutOfScreen();
};

