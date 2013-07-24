#pragma once
#include "Focusable.h"

class Clickable: public Focusable
{
public:
	// Constructor - Destructor
	Clickable();
	~Clickable();

	// Getters - Setters
	bool isClicked();

	bool isUpdateClicked();
	void setUpdateClicked(bool p_param);


protected:
	// Attributs
	bool mClicked;
	bool mUpdateClicked;

	// Methods
	void update(sf::Event p_event);


private:
	// Methods
	void updateClicked(sf::Event p_event);
};
