#pragma once
#include "KeyValueFile.h"


class RotableData
{
public:
	// Constructor - Destructor
	RotableData(void);
	~RotableData(void);

	// Getters - Setters
	float getRotationVelocity();
	void setRotationVelocity(float p_velocity);

	bool isRotationVelocityInstant();
	void setRotationVelocityInstant(bool p_instant);

	bool isRotationInfinite();
	void setRotationInfinite(bool p_infinite);

	bool isRotationInfiniteRight();
	void setRotationInfiniteRight(bool p_infiniteRight);

	// Methods
	void loadFromConfig(KeyValueFile* p_config);
	void loadFromRotableData(RotableData* p_data);


private:
	// Attributs
	float mRotationVelocity;
	bool mRotationVelocityInstant;
	bool mRotationInfinite;
	bool mRotationInfiniteRight;
};

