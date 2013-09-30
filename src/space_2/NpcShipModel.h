#pragma once
#include "NpcData.h"
#include "ShipModel.h"

// Define
#define NPCSHIPMODEL_CONFIG_ID						"id"
#define NPCSHIPMODEL_CONFIG_NAME					"name"
#define NPCSHIPMODEL_CONFIG_SHIPMODEL				"shipmodel"

class NpcShipModel : public NpcData
{
public:
	// Constructor - Destructor
	NpcShipModel(KeyValueFile *p_config);
	~NpcShipModel(void);

	// Getters - Setters
	long getIdNpcShipModel();
	void setIdNpcShipModel(long p_id);

	std::string getName();
	void setName(std::string p_name);

	ShipModel *getShipModel();
	void setShipModel(ShipModel *p_model);

	// Methods
	void loadFromConfig(KeyValueFile *p_config);


private:
	// Attributs
	long mIdNpcShipModel;
	std::string mName;
	ShipModel *mShipModel;
};

