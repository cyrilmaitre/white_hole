#include "Block.h"
#include "Manager.h"

//******************************
// Define
//******************************
#define DEFAULT_COLOR						sf::Color(255,255,0,0)
#define DEFAULT_FONTSIZE					ManagerConfig::FontSize::Medium
#define DEFAULT_FONTCOLOR					sf::Color(255,255,255)
#define DEFAULT_FONTSTYLE					sf::Text::Style::Regular
#define FONTSIZE_MIN						1	
#define FONTSIZE_MAX						50
#define DEFAULT_BORDERSIZE					0
#define BORDERSIZE_MIN						0
#define DEFAULT_BACKGROUNDCOLOR				sf::Color(255,255,255)
#define DEFAULT_BORDERCOLOR					sf::Color(0,0,0)
#define DEFAULT_OVERLAYCOLOR_DISABLE		sf::Color(48, 48, 48, 120)


//******************************
// Constructor - Destructor
//******************************
Block::Block()
{
	this->mBackgroundImage = NULL;
	this->mBackgroundImageFocus = NULL;
	this->mBackgroundImageOver = NULL;

	this->mFont = NULL;
	this->mFontStyle = DEFAULT_FONTSTYLE;
	this->mFontSize = -1;
	this->mFontColor = DEFAULT_COLOR;

	this->mBackgroundColor = DEFAULT_COLOR;
	this->mBackgroundColorFocus = DEFAULT_COLOR;
	this->mBackgroundColorOver = DEFAULT_COLOR;
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);

	this->mBorderColor = DEFAULT_COLOR;
	this->mBorderColorFocus = DEFAULT_COLOR;
	this->mBorderColorOver = DEFAULT_COLOR;
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);

	this->mBorderSize = -1;
	this->mBorderSizeFocus = -1;
	this->mBorderSizeOver = -1;
	this->setBorderSize(DEFAULT_BORDERSIZE, true);

	this->setOverlayDisableColor(DEFAULT_OVERLAYCOLOR_DISABLE);
	this->notifyPositionChanged();
	this->notifySizeChanged();
}

Block::~Block(void)
{
	if(this->mBackgroundImage != NULL)
		delete this->mBackgroundImage;

	if(this->mBackgroundImageFocus != NULL)
		delete this->mBackgroundImageFocus;

	if(this->mBackgroundImageOver != NULL)
		delete this->mBackgroundImageOver;
}


//******************************
// Getters - Setters
//******************************
sf::Color Block::getBackgroundColor()
{
	return this->mBackgroundColor;
}

void Block::setBackgroundColor( sf::Color p_color, bool setAll )
{
	if(this->mBackgroundColor != p_color)
	{
		this->mBackgroundColor = p_color;
		this->mBackground.setFillColor(this->mBackgroundColor);
	}

	if(setAll)
	{
		this->setBackgroundColorFocus(p_color);
		this->setBackgroundColorOver(p_color);
	}
}

sf::Color Block::getBackgroundColorOver()
{
	return this->mBackgroundColorOver;
}

void Block::setBackgroundColorOver( sf::Color p_color )
{
	if(this->mBackgroundColorOver != p_color)
	{
		this->mBackgroundColorOver = p_color;
		this->mBackgroundOver.setFillColor(this->mBackgroundColorOver);
	}
}

sf::Color Block::getBackgroundColorFocus()
{
	return this->mBackgroundColorFocus;
}

void Block::setBackgroundColorFocus( sf::Color p_color )
{
	if(this->mBackgroundColorFocus != p_color)
	{
		this->mBackgroundColorFocus = p_color;
		this->mBackgroundFocus.setFillColor(this->mBackgroundColorFocus);
	}
}

sf::Sprite* Block::getBackgroundImage()
{
	return this->mBackgroundImage;
}

void Block::setBackgroundImage( sf::Texture *p_image, bool scale, bool setAll )
{
	if(this->mBackgroundImage == NULL)
		this->mBackgroundImage = new sf::Sprite();

	this->mBackgroundImage->setTexture(*p_image);
	this->mBackgroundImage->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImage->setScale((float)this->getWidth() / (float)(this->mBackgroundImage->getTexture()->getSize().x), (float)this->getHeight() / (float)(this->mBackgroundImage->getTexture()->getSize().y));

	if(setAll)
	{
		this->setBackgroundImageFocus(p_image, scale);
		this->setBackgroundImageOver(p_image, scale);
	}
}

void Block::setBackgroundImage( sf::Sprite *p_sprite, bool scale )
{
	if(this->mBackgroundImage != NULL)
		delete this->mBackgroundImage;

	this->mBackgroundImage = p_sprite;
	this->mBackgroundImage->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImage->setScale((float)this->getWidth() / (float)(this->mBackgroundImage->getTextureRect().width), (float)this->getHeight() / (float)(this->mBackgroundImage->getTextureRect().height));
}

sf::Sprite* Block::getBackgroundImageOver()
{
	return this->mBackgroundImageOver;
}

void Block::setBackgroundImageOver( sf::Texture *p_image, bool scale )
{
	if(this->mBackgroundImageOver == NULL)
		this->mBackgroundImageOver = new sf::Sprite();

	this->mBackgroundImageOver->setTexture(*p_image);
	this->mBackgroundImageOver->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImageOver->setScale((float)this->getWidth() / (float)(this->mBackgroundImageOver->getTexture()->getSize().x), (float)this->getHeight() / (float)this->mBackgroundImageOver->getTexture()->getSize().y);
}

void Block::setBackgroundImageOver( sf::Sprite *p_sprite, bool scale )
{
	if(this->mBackgroundImageOver != NULL)
		delete this->mBackgroundImageOver;

	this->mBackgroundImageOver = p_sprite;
	this->mBackgroundImageOver->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImageOver->setScale((float)this->getWidth() / (float)(this->mBackgroundImageOver->getTextureRect().width), (float)this->getHeight() / (float)this->mBackgroundImageOver->getTextureRect().height);
}

sf::Sprite* Block::getBackgroundImageFocus()
{
	return this->mBackgroundImageFocus;
}

void Block::setBackgroundImageFocus( sf::Texture *p_image, bool scale )
{
	if(this->mBackgroundImageFocus == NULL)
		this->mBackgroundImageFocus = new sf::Sprite();

	this->mBackgroundImageFocus->setTexture(*p_image);
	this->mBackgroundImageFocus->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImageFocus->setScale((float)this->getWidth() / (float)(this->mBackgroundImageFocus->getTexture()->getSize().x), (float)this->getHeight() / (float)(this->mBackgroundImageFocus->getTexture()->getSize().y));
}

void Block::setBackgroundImageFocus( sf::Sprite *p_sprite, bool scale )
{
	if(this->mBackgroundImageFocus != NULL)
		delete this->mBackgroundImageFocus;

	this->mBackgroundImageFocus = p_sprite;
	this->mBackgroundImageFocus->setPosition((float)this->getX(), (float)this->getY());
	if(scale)
		this->mBackgroundImageFocus->setScale((float)this->getWidth() / (float)(this->mBackgroundImageFocus->getTextureRect().width), (float)this->getHeight() / (float)(this->mBackgroundImageFocus->getTextureRect().height));
}

sf::Color Block::getBorderColor()
{
	return this->mBorderColor;
}

void Block::setBorderColor( sf::Color p_color, bool setAll )
{
	if(this->mBorderColor != p_color)
	{
		this->mBorderColor = p_color;
		this->mBorderTop.setFillColor(this->mBorderColor);
		this->mBorderRight.setFillColor(this->mBorderColor);
		this->mBorderBottom.setFillColor(this->mBorderColor);
		this->mBorderLeft.setFillColor(this->mBorderColor);
	}
	
	if(setAll)
	{
		this->setBorderColorFocus(p_color);
		this->setBorderColorOver(p_color);
	}
}

sf::Color Block::getBorderColorOver()
{
	return this->mBorderColorOver;
}

void Block::setBorderColorOver( sf::Color p_color )
{
	if(this->mBorderColorOver != p_color)
	{
		this->mBorderColorOver = p_color;
		this->mBorderOverTop.setFillColor(this->mBorderColorOver);
		this->mBorderOverRight.setFillColor(this->mBorderColorOver);
		this->mBorderOverBottom.setFillColor(this->mBorderColorOver);
		this->mBorderOverLeft.setFillColor(this->mBorderColorOver);
	}
}

sf::Color Block::getBorderColorFocus()
{
	return this->mBorderColorFocus;
}

void Block::setBorderColorFocus( sf::Color p_color )
{
	if(this->mBorderColorFocus != p_color)
	{
		this->mBorderColorFocus = p_color;
		this->mBorderFocusTop.setFillColor(this->mBorderColorFocus);
		this->mBorderFocusRight.setFillColor(this->mBorderColorFocus);
		this->mBorderFocusBottom.setFillColor(this->mBorderColorFocus);
		this->mBorderFocusLeft.setFillColor(this->mBorderColorFocus);
	}
}

int Block::getBorderSize()
{
	return this->mBorderSize;
}

int Block::getBorderSizeOver()
{
	return this->mBorderSizeOver;
}

int Block::getBorderSizeFocus()
{
	return this->mBorderSizeFocus;
}

bool Block::setBorderSize( int p_borderSize, bool setAll )
{
	if(p_borderSize < BORDERSIZE_MIN)
		p_borderSize = BORDERSIZE_MIN;

	bool borderSizeChanged = false;
	if(this->mBorderSize != p_borderSize)
	{
		this->mBorderSize = p_borderSize;
		borderSizeChanged = true;
	}

	if(setAll)
	{
		borderSizeChanged = this->setBorderSizeFocus(p_borderSize, false) || borderSizeChanged;
		borderSizeChanged = this->setBorderSizeOver(p_borderSize, false) || borderSizeChanged;
	}

	if(borderSizeChanged)
		this->notifyBorderSizeChanged();

	return borderSizeChanged;
}

bool Block::setBorderSizeOver( int p_borderSize, bool p_notify )
{
	if(p_borderSize < BORDERSIZE_MIN)
		p_borderSize = BORDERSIZE_MIN;

	if(this->mBorderSizeOver != p_borderSize)
	{
		this->mBorderSizeOver = p_borderSize;
		if(p_notify)
			this->notifyBorderSizeChanged();
		return true;
	}

	return false;
}

bool Block::setBorderSizeFocus( int p_borderSize, bool p_notify )
{
	if(p_borderSize < BORDERSIZE_MIN)
		p_borderSize = BORDERSIZE_MIN;

	if(this->mBorderSizeFocus != p_borderSize)
	{
		this->mBorderSizeFocus = p_borderSize;
		if(p_notify)
			this->notifyBorderSizeChanged();
		return true;
	}
	
	return false;
}

sf::Font* Block::getFont()
{
	return this->mFont;
}

void Block::setFont( sf::Font* p_font )
{
	if(this->mFont != p_font)
	{
		this->mFont = p_font;
		this->notifyFontChanged();
	}
}

sf::Text::Style Block::getFontStyle()
{
	return this->mFontStyle;
}

void Block::setFontStyle( sf::Text::Style p_style )
{
	if(this->mFontStyle != p_style)
	{
		this->mFontStyle = p_style;
		this->notifyFontStyleChanged();
	}
}

int Block::getFontSize()
{
	return this->mFontSize;
}

void Block::setFontSize( int p_fontSize )
{
	if(p_fontSize < FONTSIZE_MIN)
		p_fontSize = FONTSIZE_MIN;

	if(this->mFontSize != p_fontSize)
	{
		this->mFontSize = p_fontSize;
		this->notifyFontSizeChanged();
	}
}

sf::Color Block::getFontColor()
{
	return this->mFontColor;
}

void Block::setFontColor( sf::Color p_color )
{
	if(this->mFontColor != p_color)
	{
		this->mFontColor = p_color;
		this->notifyFontColorChanged();
	}
}

sf::Color Block::getOverlayDisableColor()
{
	return this->mOverlayDisable.getFillColor();
}

void Block::setOverlayDisableColor( sf::Color p_color )
{
	if(this->getOverlayDisableColor() != p_color)
	{
		this->mOverlayDisable.setFillColor(p_color);
	}
}


//******************************
// Graphic
//******************************
void Block::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Selectable::update(p_event);
	}
}

void Block::updatePosition()
{
	this->mBackground.setPosition((float)this->getX(), (float)this->getY());
	this->mBackgroundOver.setPosition((float)this->getX(), (float)this->getY());
	this->mBackgroundFocus.setPosition((float)this->getX(), (float)this->getY());

	if(this->mBackgroundImage != NULL)
		this->mBackgroundImage->setPosition((float)this->getX(), (float)this->getY());
	
	if(this->mBackgroundImageOver != NULL)
		this->mBackgroundImageOver->setPosition((float)this->getX(), (float)this->getY());
	
	if(this->mBackgroundImageFocus != NULL)
		this->mBackgroundImageFocus->setPosition((float)this->getX(), (float)this->getY());

	this->mBorderTop.setPosition((float)(this->getX() - this->getBorderSize()), (float)(this->getY() - this->getBorderSize()));
	this->mBorderBottom.setPosition((float)(this->getX() - this->getBorderSize()), (float)(this->getY() + this->getHeight()));
	this->mBorderLeft.setPosition((float)(this->getX() - this->getBorderSize()), (float)(this->getY()));
	this->mBorderRight.setPosition((float)(this->getX() + this->getWidth()), (float)(this->getY()));

	this->mBorderOverTop.setPosition((float)(this->getX() - this->getBorderSizeOver()), (float)(this->getY() - this->getBorderSizeOver()));
	this->mBorderOverBottom.setPosition((float)(this->getX() - this->getBorderSizeOver()), (float)(this->getY() + this->getHeight()));
	this->mBorderOverLeft.setPosition((float)(this->getX() - this->getBorderSizeOver()), (float)(this->getY()));
	this->mBorderOverRight.setPosition((float)(this->getX() + this->getWidth()), (float)(this->getY()));

	this->mBorderFocusTop.setPosition((float)(this->getX() - this->getBorderSizeFocus()), (float)(this->getY() - this->getBorderSizeFocus()));
	this->mBorderFocusBottom.setPosition((float)(this->getX() - this->getBorderSizeFocus()), (float)(this->getY() + this->getHeight()));
	this->mBorderFocusLeft.setPosition((float)(this->getX() - this->getBorderSizeFocus()), (float)(this->getY()));
	this->mBorderFocusRight.setPosition((float)(this->getX() + this->getWidth()), (float)(this->getY()));

	this->mOverlayDisable.setPosition(this->getX() - this->getBorderSize(), this->getY() - this->getBorderSize());
}

void Block::updateSize()
{
	this->mBackground.setSize(sf::Vector2f((float)this->getWidth(), (float)this->getHeight()));
	this->mBackgroundOver.setSize(sf::Vector2f((float)this->getWidth(), (float)this->getHeight()));
	this->mBackgroundFocus.setSize(sf::Vector2f((float)this->getWidth(), (float)this->getHeight()));
	this->mOverlayDisable.setSize(sf::Vector2f(this->getWidth() + this->getBorderSize() * 2, this->getHeight() + this->getBorderSize() * 2));
}

void Block::updateBorder()
{
	if(this->mBorderSize > 0)
	{
		this->mBorderTop.setSize(sf::Vector2f((float)(2 * this->mBorderSize + this->getWidth()), (float)this->mBorderSize));
		this->mBorderBottom.setSize(sf::Vector2f((float)(2 * this->mBorderSize + this->getWidth()), (float)this->mBorderSize));
		this->mBorderLeft.setSize(sf::Vector2f((float)this->mBorderSize, (float)(this->getHeight())));
		this->mBorderRight.setSize(sf::Vector2f((float)this->mBorderSize, (float)(this->getHeight())));
	}

	if(this->mBorderSizeOver > 0)
	{
		this->mBorderOverTop.setSize(sf::Vector2f((float)(2 * this->mBorderSizeOver + this->getWidth()), (float)this->mBorderSizeOver));
		this->mBorderOverBottom.setSize(sf::Vector2f((float)(2 * this->mBorderSizeOver + this->getWidth()), (float)this->mBorderSizeOver));
		this->mBorderOverLeft.setSize(sf::Vector2f((float)this->mBorderSizeOver, (float)(this->getHeight())));
		this->mBorderOverRight.setSize(sf::Vector2f((float)this->mBorderSizeOver, (float)(this->getHeight())));
	}

	if(this->mBorderSizeFocus > 0)
	{
		this->mBorderFocusTop.setSize(sf::Vector2f((float)(2 * this->mBorderSizeFocus + this->getWidth()), (float)this->mBorderSizeFocus));
		this->mBorderFocusBottom.setSize(sf::Vector2f((float)(2 * this->mBorderSizeFocus + this->getWidth()), (float)this->mBorderSizeFocus));
		this->mBorderFocusLeft.setSize(sf::Vector2f((float)this->mBorderSizeFocus, (float)(this->getHeight())));
		this->mBorderFocusRight.setSize(sf::Vector2f((float)this->mBorderSizeFocus, (float)(this->getHeight())));
	}
}

void Block::draw()
{
	if(this->isVisible())
	{
		this->drawBackground();
		this->drawBorder();
		if(!this->isEnable())
			this->drawOverlayDisable();
	}
}

void Block::drawBackground()
{
	// Draw background
	if(this->mFocus && this->isEnable())
		Resource::resource->getApp()->draw(this->mBackgroundFocus);
	else if(this->mMouseOver && this->isEnable())
		Resource::resource->getApp()->draw(this->mBackgroundOver);
	else
		Resource::resource->getApp()->draw(this->mBackground);

	// Draw background Image
	if(this->mFocus && this->isEnable())
	{
		if(this->mBackgroundImageFocus != NULL)
			Resource::resource->getApp()->draw(*this->mBackgroundImageFocus);
		else if(this->mBackgroundImage != NULL)
			Resource::resource->getApp()->draw(*this->mBackgroundImage);
	}
	else if(this->mMouseOver && this->isEnable())
	{
		if(this->mBackgroundImageOver != NULL)
			Resource::resource->getApp()->draw(*this->mBackgroundImageOver);
		else if(this->mBackgroundImage != NULL)
			Resource::resource->getApp()->draw(*this->mBackgroundImage);
	}
	else
	{
		if(this->mBackgroundImage != NULL)
			Resource::resource->getApp()->draw(*this->mBackgroundImage);
	}
}

void Block::drawBorder()
{
	if(this->mBorderSize == 0)
		return;

	if(this->mFocus && this->isEnable())
	{
		if(this->getBorderSizeFocus() > 0)
		{
			Resource::resource->getApp()->draw(this->mBorderFocusTop);
			Resource::resource->getApp()->draw(this->mBorderFocusRight);
			Resource::resource->getApp()->draw(this->mBorderFocusBottom);
			Resource::resource->getApp()->draw(this->mBorderFocusLeft);
		}
	}
	else if(this->mMouseOver && this->isEnable())
	{
		if(this->getBorderSizeOver() > 0)
		{
			Resource::resource->getApp()->draw(this->mBorderOverTop);
			Resource::resource->getApp()->draw(this->mBorderOverRight);
			Resource::resource->getApp()->draw(this->mBorderOverBottom);
			Resource::resource->getApp()->draw(this->mBorderOverLeft);
		}
	}
	else
	{
		if(this->getBorderSize() > 0)
		{
			Resource::resource->getApp()->draw(this->mBorderTop);
			Resource::resource->getApp()->draw(this->mBorderRight);
			Resource::resource->getApp()->draw(this->mBorderBottom);
			Resource::resource->getApp()->draw(this->mBorderLeft);
		}
	}
}

void Block::drawOverlayDisable()
{
	Resource::resource->getApp()->draw(this->mOverlayDisable);
}

void Block::notifyPositionChanged()
{
	Selectable::notifyPositionChanged();
	this->updatePosition();
}

void Block::notifySizeChanged()
{
	Selectable::notifySizeChanged();
	this->updateSize();
	this->updateBorder();
	this->updatePosition();
}

void Block::notifyBorderSizeChanged()
{
	this->updateSize();
	this->updateBorder();
	this->updatePosition();
}

void Block::notifyFontChanged()
{
	
}

void Block::notifyFontColorChanged()
{

}

void Block::notifyFontSizeChanged()
{

}

void Block::notifyFontStyleChanged()
{

}





