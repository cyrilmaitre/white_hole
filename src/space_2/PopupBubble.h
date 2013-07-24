#pragma once
#include "TextMultiLine.h"
#include "Clock.h"

class PopupBubble: public TextMultiLine
{
public:
	// Constructor - Destructor
	PopupBubble(Object* p_trigger);
	~PopupBubble(void);

	// Getters - Setters
	double getDelay();
	void setDelay(double p_delay);

	void setArrowPointerX(int p_x);
	void setArrowPointerY(int p_y);

	// Methods
	void update();
	void update(sf::Event p_event);
	void draw();
	static void drawAll();


protected:
	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyVisibleChanged();


private:
	// Attributs
	sf::Sprite mPopupBubbleArrow;
	Object* mTrigger;
	double mDelay;
	mks::Clock mClockDelay;

	// Methods
	void updateArrowPosition();

	// Statics
	static std::list<PopupBubble*> mPopupBubbles;
};