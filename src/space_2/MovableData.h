#pragma once
#include "Resource.h"
#include "KeyValueFile.h"


class MovableData
{
public:
	// Constructor - Destructor
	MovableData(void);
	~MovableData(void);

	// Getters - Setters
	virtual float getVelocityMax();
	void setVelocityMax(float p_velocityMax);

	virtual float getQuickening();
	void setQuickening(float p_quickening);

	int getReactorCount();
	void setReactorCount(int p_count);

	int getReactorSize();
	void setReactorSize(int p_size);

	sf::Vector2i getReactorPosition(int p_index);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromMovableData(MovableData* p_object);


protected:
	// Attributs
	float mVelocityMax;
	float mQuickening;

	int mReactorCount;
	int mReactorSize;
	std::string mReactorPositionJson;
	std::vector<sf::Vector2i> mReactorPosition;


private:
	// Methods
	void processReactorPositionJson();
};

