#pragma once
#include "Focusable.h"
#include "Scrollbar.h"

class ScrollbarThumb: public Focusable
{
public:
	// Constructor - Destructor
	ScrollbarThumb();
	~ScrollbarThumb();

	// Getters - Setters
	void setX(double p_x, bool p_notify = true);
	void setY(double p_y, bool p_notify = true);

	Scrollbar::ScrollBarOrientation getOrientation();
	void setOrientation(Scrollbar::ScrollBarOrientation p_orientation);

	int getPositionMin();
	void setPositionMin(int p_min);

	int getPositionMax();
	void setPositionMax(int p_max);

	// Methods
	void draw();
	void update(sf::Event p_event);


private:
	// Attributs
	Scrollbar::ScrollBarOrientation mOrientation;
	int mPositionMin;
	int mPositionMax;
	SpriteParameter *mScrollBarSprite;

	sf::Sprite mThumbTop;
	sf::Sprite mThumbMid;
	sf::Sprite mThumbBottom;

	// Methods
	void notifyOrientationChanged();
	void notifyPositionChanged();
	void notifyMouseOverChanged();
	void notifyFocusChanged();

	void updateSprite();
	void updateSpritePosition();
};

