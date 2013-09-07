#pragma once
#include "Button.h"
#include "SpriteParameter.h"

class ScrollbarThumb;

// Define
#define SCROLLBAR_WIDTH				22

class Scrollbar: public Object
{
public:
	// Enum
	enum ScrollBarOrientation
	{
		Horizontal = 0,
		Vertical
	};

	// Constructor - Destructor
	Scrollbar(ScrollBarOrientation p_orientation = ScrollBarOrientation::Vertical);
	~Scrollbar(void);

	// Getters - Setters
	Button* getButtonScrollUp();
	Button* getButtonScrollDown();

	ScrollBarOrientation getOrientation();
	void setOrientation(ScrollBarOrientation p_orientation);

	int getScrollOffsetInPx();
	void setScrollOffsetInPx(int p_offset, bool p_notify = true);

	float getScrollOffsetInPercent();
	void setScrollOffsetInPercent(float p_percent, bool p_notify = true);

	int getOffsetOnScroll();
	void setOffsetOnScroll(int p_offset);

	int getScrollAreaHeight();
	void setScrollAreaHeight(int p_size);

	bool isThumbPositionChanged();
	bool isUsefull();

	bool isButtonScrollActionDelegated();
	void setButtonScrollActionDelegated(bool p_delegated);

	void setScrollBarHeight(int p_size);

	// Methods
	void scrollUp();
	void scrollDown();

	void updateSpritePosition();
	void updateButtonPosition();
	void updateThumbPosition();
	void updateThumbPositionRange();

	void update(sf::Event myEvent);
	void draw();


protected:
	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyOrientationChanged();


private:
	// Attributs
	ScrollBarOrientation mOrientation;
	int mScrollAreaHeight;
	int mOffsetOnScroll;

	sf::Sprite mTrackTop;
	sf::Sprite mTrackMid;
	sf::Sprite mTrackBottom;

	SpriteParameter *mScrollBarSprite;
	ScrollbarThumb *mScrollBarThumb;
	Button mButtonScrollUp;
	Button mButtonScrollDown;
	bool mButtonScrollActionDelegated;

	// Getters - Setters
	int getThumbHeight();
	int getThumbHeightMax();
	int getThumbHeightRange();
			
	double getThumbPosition();
	void setThumbPosition(double p_position, bool p_notify = true);

	double getThumbOffset();
	void setThumbOffset(double p_offset, bool p_notify = true);

	float getAreaDisplayedPercent();
	bool hasThumbFocus();

	// Methods
	void drawTrack();
	void updateSprite();
	void updateThumbSize();
};

// Define
#define IC_SCROLLBAR_V_TACK_UP					"0-0"
#define IC_SCROLLBAR_V_TACK_MID					"0-1"
#define IC_SCROLLBAR_V_TACK_DOWN				"0-2"
#define IC_SCROLLBAR_V_THUMB_GRID				"1-0"
#define IC_SCROLLBAR_V_THUMB_UP					"0-3"
#define IC_SCROLLBAR_V_THUMB_MID				"0-4"
#define IC_SCROLLBAR_V_THUMB_DOWN				"0-5"
#define IC_SCROLLBAR_V_THUMB_UP_OVER			"1-3"
#define IC_SCROLLBAR_V_THUMB_MID_OVER			"1-4"
#define IC_SCROLLBAR_V_THUMB_DOWN_OVER			"1-5"
#define IC_SCROLLBAR_V_THUMB_UP_FOCUS			"2-3"
#define IC_SCROLLBAR_V_THUMB_MID_FOCUS			"2-4"
#define IC_SCROLLBAR_V_THUMB_DOWN_FOCUS			"2-5"
#define IC_SCROLLBAR_V_BUTTON_UP				"0-6"
#define IC_SCROLLBAR_V_BUTTON_DOWN				"0-7"
#define IC_SCROLLBAR_V_BUTTON_UP_OVER			"1-6"
#define IC_SCROLLBAR_V_BUTTON_DOWN_OVER			"1-7"
#define IC_SCROLLBAR_V_BUTTON_UP_FOCUS			"2-6"
#define IC_SCROLLBAR_V_BUTTON_DOWN_FOCUS		"2-7"

#define IC_SCROLLBAR_H_TACK_UP					"3-0"
#define IC_SCROLLBAR_H_TACK_MID					"3-1"
#define IC_SCROLLBAR_H_TACK_DOWN				"3-2"
#define IC_SCROLLBAR_H_THUMB_GRID				"4-0"
#define IC_SCROLLBAR_H_THUMB_UP					"3-3"
#define IC_SCROLLBAR_H_THUMB_MID				"3-4"
#define IC_SCROLLBAR_H_THUMB_DOWN				"3-5"
#define IC_SCROLLBAR_H_THUMB_UP_OVER			"4-3"
#define IC_SCROLLBAR_H_THUMB_MID_OVER			"4-4"
#define IC_SCROLLBAR_H_THUMB_DOWN_OVER			"4-5"
#define IC_SCROLLBAR_H_THUMB_UP_FOCUS			"5-3"
#define IC_SCROLLBAR_H_THUMB_MID_FOCUS			"5-4"
#define IC_SCROLLBAR_H_THUMB_DOWN_FOCUS			"5-5"
#define IC_SCROLLBAR_H_BUTTON_UP				"3-6"
#define IC_SCROLLBAR_H_BUTTON_DOWN				"3-7"
#define IC_SCROLLBAR_H_BUTTON_UP_OVER			"4-6"
#define IC_SCROLLBAR_H_BUTTON_DOWN_OVER			"4-7"
#define IC_SCROLLBAR_H_BUTTON_UP_FOCUS			"5-6"
#define IC_SCROLLBAR_H_BUTTON_DOWN_FOCUS		"5-7"	
