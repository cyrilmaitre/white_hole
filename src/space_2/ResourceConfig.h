#pragma once
#include "ManagerConfig.h"


class ResourceConfig : public ManagerConfig
{
public:
	// Constructor - Destructor
	ResourceConfig(void);
	~ResourceConfig(void);

	// Methods
	sf::Font* getFontDefault();
	sf::Font* getFontUi();
	sf::Font* getFontUiTheme();
	sf::RenderWindow* getRenderWindowDefault();
	SpriteParameter* getSpriteParameterScrollbar();
	sf::Texture* getTexturePopupBubbleArrow();

	int getFontSizeTiny();
	int getFontSizeSmall();
	int getFontSizeMedium();
	int getFontSizeLarge();
	int getFontSizeHuge();

	std::string getHttpHost();
	unsigned short getHttpHostPort();
};

