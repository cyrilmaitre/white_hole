#pragma once
#include "SpriteParameter.h"

class ManagerConfig
{
public:
	// Enum
	enum FontSize
	{
		Tiny = 13,
		Small = 14,
		Medium = 15,
		Large = 18,
		Huge = 20
	};

	// Constructor - Destructor
	ManagerConfig(void);
	~ManagerConfig(void);

	// Getters - Setters
	virtual sf::Font* getFontDefault() = 0;
	virtual sf::Font* getFontUi() = 0;
	virtual sf::Font* getFontUiTheme() = 0;
	virtual sf::RenderWindow* getRenderWindowDefault() = 0;

	virtual SpriteParameter* getSpriteParameterScrollbar() = 0;
	virtual sf::Texture* getTexturePopupBubbleArrow() = 0;

	virtual int getFontSizeTiny() = 0;
	virtual int getFontSizeSmall() = 0;
	virtual int getFontSizeMedium() = 0;
	virtual int getFontSizeLarge() = 0;
	virtual int getFontSizeHuge() = 0;

	virtual std::string getHttpHost() = 0;
	virtual unsigned short getHttpHostPort() = 0;
};



