#pragma once
#include "Selectable.h"

class Block: public Selectable
{
public:
	// Constructor - Destructor
	Block();
	~Block();

	// Getters - Setters
	sf::Color getBackgroundColor();
	void setBackgroundColor(sf::Color p_color, bool p_setAll = false);

	sf::Color getBackgroundColorOver();
	void setBackgroundColorOver(sf::Color p_color);

	sf::Color getBackgroundColorFocus();
	void setBackgroundColorFocus(sf::Color p_color);

	sf::Sprite* getBackgroundImage();
	void setBackgroundImage(sf::Texture *p_image, bool p_scale = true, bool p_setAll = false);
	void setBackgroundImage(sf::Sprite *p_sprite, bool p_scale = true);
			
	sf::Sprite* getBackgroundImageOver();
	void setBackgroundImageOver(sf::Texture *p_image, bool p_scale = true);
	void setBackgroundImageOver(sf::Sprite *p_sprite, bool p_scale = true);

	sf::Sprite* getBackgroundImageFocus();
	void setBackgroundImageFocus(sf::Texture *p_image, bool p_scale = true);
	void setBackgroundImageFocus(sf::Sprite *p_sprite, bool p_scale = true);

	sf::Color getBorderColor();
	void setBorderColor(sf::Color p_color, bool p_setAll = false);

	sf::Color getBorderColorOver();
	void setBorderColorOver(sf::Color p_color);

	sf::Color getBorderColorFocus();
	void setBorderColorFocus(sf::Color p_color);

	int getBorderSize();
	bool setBorderSize(int p_borderSize, bool p_setAll = false);

	int getBorderSizeOver();
	bool setBorderSizeOver(int p_borderSize, bool p_notify = true);

	int getBorderSizeFocus();
	bool setBorderSizeFocus(int p_borderSize, bool p_notify = true);

	sf::Font* getFont();
	void setFont(sf::Font* p_font);

	sf::Text::Style getFontStyle();
	void setFontStyle(sf::Text::Style p_style);

	sf::Color getFontColor();
	void setFontColor(sf::Color p_color);

	int getFontSize();
	void setFontSize(int p_fontSize);

	sf::Color getOverlayDisableColor();
	void setOverlayDisableColor(sf::Color p_color);

	// Methods
	void draw();
	void update(sf::Event p_event);


protected:
	// Attributs
	sf::RectangleShape mBackground;
	sf::RectangleShape mBackgroundOver;
	sf::RectangleShape mBackgroundFocus;
	sf::Color mBackgroundColor;
	sf::Color mBackgroundColorOver;
	sf::Color mBackgroundColorFocus;
	sf::Sprite *mBackgroundImage;
	sf::Sprite *mBackgroundImageOver;
	sf::Sprite *mBackgroundImageFocus;

	sf::RectangleShape mBorderTop;
	sf::RectangleShape mBorderRight;
	sf::RectangleShape mBorderBottom;
	sf::RectangleShape mBorderLeft;
	sf::RectangleShape mBorderOverTop;
	sf::RectangleShape mBorderOverRight;
	sf::RectangleShape mBorderOverBottom;
	sf::RectangleShape mBorderOverLeft;
	sf::RectangleShape mBorderFocusTop;
	sf::RectangleShape mBorderFocusRight;
	sf::RectangleShape mBorderFocusBottom;
	sf::RectangleShape mBorderFocusLeft;
	sf::Color mBorderColor;
	sf::Color mBorderColorOver;
	sf::Color mBorderColorFocus;
	int mBorderSize;
	int mBorderSizeOver;
	int mBorderSizeFocus;

	sf::Font* mFont;
	sf::Text::Style mFontStyle;
	sf::Color mFontColor;
	int mFontSize;

	sf::RectangleShape mOverlayDisable;

	// Methods
	virtual void notifyFontChanged();
	virtual void notifyFontColorChanged();
	virtual void notifyFontSizeChanged();
	virtual void notifyFontStyleChanged();
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyBorderSizeChanged();


private:
	// Methods
	void drawBorder();
	void drawBackground();
	void drawOverlayDisable();

	void updatePosition();
	void updateSize();
	void updateBorder();
};

