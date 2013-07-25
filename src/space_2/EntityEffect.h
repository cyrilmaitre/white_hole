#pragma once
#include "Resource.h"

class Entity;

class EntityEffect
{
public:
	// Constructor - Destructor
	EntityEffect(Entity* p_entity, sf::Vector2f p_offset = sf::Vector2f(0, 0), int p_size = 0);
	~EntityEffect(void);

	// Getters - Setters
	Entity* getEntity();
	void setEntity(Entity* p_entity);

	float getOffsetX();
	void setOffsetX(float p_x);

	float getOffsetXRotate();
	void setOffsetXRotate(float p_x);

	float getOffsetY();
	void setOffsetY(float p_y);

	float getOffsetYRotate();
	void setOffsetYRotate(float p_y);

	int getSize();
	void setSize(int p_size);

	// Methods
	virtual void update();
	void updateOffsetRotate();
	virtual void draw();


protected:
	// Attributs
	Entity* mEntity;
	sf::Vector2f mOffset;
	sf::Vector2f mOffsetRotate;
	int mSize;
};

