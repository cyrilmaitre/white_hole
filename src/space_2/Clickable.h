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
	void setClicked(bool p_value);

	bool isUpdateClicked();
	void setUpdateClicked(bool p_param);


protected:
	// Attributs
	bool mClicked;
	bool mUpdateClicked;

	// Methods
	void update(sf::Event p_event);
	virtual void notifyClickedChanged();


private:
	// Methods
	void updateClicked(sf::Event p_event);
};
