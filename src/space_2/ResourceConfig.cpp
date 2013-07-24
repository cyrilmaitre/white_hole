#include "ResourceConfig.h"
#include "Resource.h"
#include "SpriteParameterFactory.h"
#include "NetworkDefine.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ResourceConfig::ResourceConfig(void)
{
}

ResourceConfig::~ResourceConfig(void)
{
}


//*************************************************************
// Methods
//*************************************************************
sf::Font* ResourceConfig::getFontDefault()
{
	return Resource::resource->getFontDefault();
}

sf::Font* ResourceConfig::getFontUi()
{
	return Resource::resource->getFontUi();
}

sf::Font* ResourceConfig::getFontUiTheme()
{
	return Resource::resource->getFontUiTheme();
}

sf::RenderWindow* ResourceConfig::getRenderWindowDefault()
{
	return Resource::resource->getApp();
}

SpriteParameter* ResourceConfig::getSpriteParameterScrollbar()
{
	return SpriteParameterFactory::getSpriteParameterScrollbar(false);
}

sf::Texture* ResourceConfig::getTexturePopupBubbleArrow()
{
	return Resource::resource->getTexture(IMG_POPUP_BUBBLE_ARROW);
}

int ResourceConfig::getFontSizeTiny()
{
	return FontSize::Tiny;
}

int ResourceConfig::getFontSizeSmall()
{
	return FontSize::Small;
}

int ResourceConfig::getFontSizeMedium()
{
	return FontSize::Medium;
}

int ResourceConfig::getFontSizeLarge()
{
	return FontSize::Large;
}

int ResourceConfig::getFontSizeHuge()
{
	return FontSize::Huge;
}

std::string ResourceConfig::getHttpHost()
{
	return NETWORK_HTTP_HOST;
}

unsigned short ResourceConfig::getHttpHostPort()
{
	return NETWORK_HTTP_HOST_PORT;
}

