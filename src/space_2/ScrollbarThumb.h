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
	void setX(double p_x, bool p_notify = true, bool p_updateOffset = true);
	void setY(double p_y, bool p_notify = true, bool p_updateOffset = true);

	Scrollbar::ScrollBarOrientation getOrientation();
	void setOrientation(Scrollbar::ScrollBarOrientation p_orientation);

	double getPositionMin();
	void setPositionMin(double p_min);
	bool isPositionMin();

	double getPositionMax();
	void setPositionMax(double p_max);
	bool isPositionMax();

	double getPositionOffset();
	void setPositionOffset(double p_offset, bool p_notify = true);

	// Methods
	void draw();
	void update(sf::Event p_event);


private:
	// Attributs
	Scrollbar::ScrollBarOrientation mOrientation;
	double mPositionMin;
	double mPositionMax;
	double mPositionOffset;
	SpriteParameter *mScrollBarSprite;

	sf::Sprite mThumbTop;
	sf::Sprite mThumbMid;
	sf::Sprite mThumbBottom;

	// Methods
	void notifyOrientationChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyMouseOverChanged();
	void notifyFocusChanged();

	void updateSprite();
	void updateSpritePosition();
};

