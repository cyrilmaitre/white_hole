#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class MapObjectModel
{
public:
	// Constructor - Destructor
	MapObjectModel(KeyValueFile* p_config);
	~MapObjectModel(void);

	// Getters - Setters
	long getIdMapObjectModel();
	void setIdMapObjectModel(long p_id);

	int getHitBoxWidth();
	void setHitBoxWidth(int p_width);

	int getHitBoxHeight();
	void setHitBoxHeight(int p_height);

	float getScaleMin();
	void setScaleMin(float p_min);

	float getScaleMax();
	void setScaleMax(float p_max);

	std::string getSprite();
	void setSprite(std::string p_sprite);

	// Methods
	float getRandomScale();
	virtual void loadFromConfig(KeyValueFile* p_config);


private:
	// Attributs
	long mIdMapObjectModel;
	int mHitBoxWidth;
	int mHitBoxHeight;
	float mScaleMin;
	float mScaleMax;
	std::string mSprite;
};

