#pragma once
#include "Block.h"
#include "Scrollbar.h"

class Scrollable: public Block
{
public:
	// Constructor - Destructor
	Scrollable();
	~Scrollable();

	// Getters - Setters
	Scrollbar* getScrollbar();
	bool hasScrollBar();

	bool isForceScrollbar();
	void setForceScrollBar(bool p_forced);

	// Methods
	void update(sf::Event p_event);
	void draw(bool p_drawScrollBar = true);


protected:
	// Attributs
	Scrollbar *mScrollBar;
	bool mForceScrollbar;

	// Methods
	void updateScrollbarVisibility();
	void notifyForceScrollbarChanged();
	virtual void notifyScrollOccured(bool p_up);
};