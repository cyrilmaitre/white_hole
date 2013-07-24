#pragma once
#include "Object.h"

class Focusable: public Object
{
public:
	// Constructor - Destructor
	Focusable();
	~Focusable();

	// Getters - Setters
	bool hasFocus();
	int getFocusOriginLocalX();
	int getFocusOriginLocalY();
	int getFocusOriginGlobalX();
	int getFocusOriginGlobalY();

	bool isUpdateFocus();
	void setUpdateFocus(bool p_param);
	bool isFocusChanged();


protected:
	// Attributs
	int mFocusOriginLocalX;
	int mFocusOriginLocalY;
	int mFocusOriginGlobalX;
	int mFocusOriginGlobalY;
	bool mFocus;
	bool mFocusChanged;
	bool mUpdateFocus;

	// Methods
	void update(sf::Event p_event);
	virtual void notifyFocusChanged();


private:
	// Methods
	void updateFocus(sf::Event p_event);
};
