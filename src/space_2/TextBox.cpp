#include "TextBox.h"
#include "Manager.h"

//*************************************************************
// Define
//*************************************************************
#define DEFAULT_FONTCOLOR				sf::Color(195,195,195)
#define DEFAULT_FONTSIZE				ManagerConfig::FontSize::Medium
#define DEFAULT_BACKGROUNDCOLOR			sf::Color(0,0,0,0)
#define DEFAULT_BORDERCOLOR				sf::Color(0,0,0,0)
#define DEFAULT_BORDERSIZE				0
#define DEFAULT_TEXT					"TextBox"
#define DEFAULT_FONTOFFSETY				-0.15


//*************************************************************
// Constructor - Destructor
//*************************************************************
TextBox::TextBox()
{
	this->setAutoResize(true);
	this->setFont(Manager::getInstance()->getConfig()->getFontDefault());
	this->setFontColor(DEFAULT_FONTCOLOR);
	this->setFontSize(DEFAULT_FONTSIZE);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);
	this->setText(DEFAULT_TEXT);
}

TextBox::~TextBox(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
bool TextBox::isAutoResize()
{
	return this->mAutoResize;
}

void TextBox::setAutoResize( bool p_auto )
{
	this->mAutoResize = p_auto;
}


//*************************************************************
// Methods
//*************************************************************
void TextBox::draw()
{
	if(this->isVisible())
	{
		Text::draw();
		Resource::resource->getApp()->draw(this->mText);
	}
}

void TextBox::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		Text::update(p_event);
	}
}

void TextBox::notifyFontChanged()
{
	Text::notifyFontChanged();
	this->mText.setFont(*this->mFont);
	this->updateText();
}

void TextBox::notifyFontStyleChanged()
{
	Text::notifyFontStyleChanged();
	this->mText.setStyle(this->mFontStyle);
	this->updateText();
}

void TextBox::notifyFontColorChanged()
{
	Text::notifyFontColorChanged();
	this->mText.setColor(this->mFontColor);
}

void TextBox::notifyFontSizeChanged()
{
	Text::notifyFontSizeChanged();
	this->mText.setCharacterSize(this->mFontSize);
	this->updateText();
	this->updateTextPosition();
}

void TextBox::notifyTextChanged()
{
	Text::notifyTextChanged();
	this->mText.setString(this->getText());
	this->updateText();
}

void TextBox::notifyPositionChanged()
{
	Text::notifyPositionChanged();
	this->updateTextPosition();
}

void TextBox::updateText()
{
	if(this->isAutoResize())
	{
		// Resize container
		this->setSize(this->mText.findCharacterPos(this->mText.getString().getSize()).x - this->getX(), this->getFontSize());
	}
	else
	{
		// Resize text
		bool tmpStringResized = false;
		int tmpTextWidth;

		sf::Text endText("...", *this->mText.getFont(), this->mText.getCharacterSize());
		endText.setPosition(0, 0);
		int endTextWidth = endText.findCharacterPos(endText.getString().getSize()).x;
		int maxWidth = this->getWidth();

		tmpTextWidth = this->mText.findCharacterPos(this->mText.getString().getSize()).x - this->getX();
		while(tmpTextWidth > maxWidth)
		{
			if(!tmpStringResized)
				maxWidth = this->getWidth() - endTextWidth;

			std::string tmpString = this->mText.getString();
			this->mText.setString(tmpString.substr(0, tmpString.length() - 1));
			tmpTextWidth = this->mText.findCharacterPos(this->mText.getString().getSize()).x - this->getX();
			tmpStringResized = true;
		}

		if(tmpStringResized)
		{
			// Replace 3 last letter by "..."
			std::string tmpString = this->mText.getString();
			tmpString = tmpString.append("...");
			this->mText.setString(tmpString);
		}
	}
}

void TextBox::updateTextPosition()
{
	this->mText.setPosition((float)this->getX(), (float)(this->getY() + this->getFontSize() * DEFAULT_FONTOFFSETY));
}


