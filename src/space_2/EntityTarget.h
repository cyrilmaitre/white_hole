#pragma once

class Entity;

class EntityTarget
{
public:
	// Constructor - Destructor
	EntityTarget(void);
	~EntityTarget(void);

	// Getters - Setters
	long getEntityId();

	Entity* getEntity();
	void setEntity(Entity* p_target);

	bool isEntityValid();
	bool isEntityChanged();

	// Method
	void notifyEntityChanged();


private:
	// Attributs
	long mEntitytId;
	Entity* mEntity;
	bool mEntityChanged;
};

