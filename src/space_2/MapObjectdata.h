#pragma once
#include "KeyValueFile.h"

// Define
#define MAPOBJECTDATA_CONFIG_WIDTH		"width"
#define MAPOBJECTDATA_CONFIG_HEIGHT		"height"

class MapObjectData
{
public:
	// Constructor - Destructor
	MapObjectData(void);
	~MapObjectData(void);

	// Getters - Setters
	virtual int getWidth();
	void setWidth(int p_width);

	virtual int getHeight();
	void setHeight(int p_height);

	int getRadius();

	// Methods
	void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	int mWidth;
	int mHeight;
};

