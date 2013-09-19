#pragma once
#include "Block.h"


class PopupManager
{
public:
	// Getters - Setters
	static PopupManager* getInstance();

	// Methods
	void addPopup(Block* p_popup);
	void removePopup(Block* p_popup);
	void draw();


private:
	// Constructor - Destructor
	PopupManager(void);
	~PopupManager(void);

	// Attributs
	std::vector<Block*> mPopups;
	static PopupManager* mInstance;
};

