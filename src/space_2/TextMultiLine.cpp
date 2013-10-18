#include "TextMultiLine.h"
#include "SplitString.h"
#include "TextBox.h"
#include "Manager.h"

//*************************************************************
// Define
//*************************************************************
#define DEFAULT_WIDTH						200	
#define WIDTH_MIN_FORADDLINE				20
#define DEFAULT_HEIGHT						0		
#define DEFAULT_DELIMETER					"<br/>"
#define DEFAULT_INTERLINE_SIZE				2
#define DEFAULT_INTERLINE_COLOR				sf::Color(0,0,0,0)
#define DEFAULT_BACKGROUNDCOLOR				sf::Color(0,0,0,0)
#define DEFAULT_BORDERCOLOR					sf::Color(0,0,0,0)
#define DEFAULT_FONTCOLOR					sf::Color(195,195,195)
#define DEFAULT_FONTSIZE					ManagerConfig::FontSize::Medium
#define DEFAULT_TEXT						""


//*************************************************************
// Constructor - Destructor
//*************************************************************
TextMultiLine::TextMultiLine( bool p_autoResizeHeight )
{
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->setInterlineSize(DEFAULT_INTERLINE_SIZE);
	this->setFont(Manager::getInstance()->getConfig()->getFontDefault());
	this->setFontColor(DEFAULT_FONTCOLOR);
	this->setFontSize(DEFAULT_FONTSIZE);
	this->setDelimeter(DEFAULT_DELIMETER);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);
	this->setAutoResizeHeight(p_autoResizeHeight);
	this->setSeparatorColor(DEFAULT_INTERLINE_COLOR);
	this->setText(DEFAULT_TEXT);
}

TextMultiLine::~TextMultiLine(void)
{
}


//******************************
// Getters - Setters
//******************************
std::string TextMultiLine::getText()
{
	return this->mText;
}

void TextMultiLine::setText( std::string p_text )
{
	if(this->mText != p_text)
	{
		this->mText = p_text;
		this->notifyTextChanged();
	}
}

std::string TextMultiLine::getDelimeter()
{
	return this->mDelimeter;
}

void TextMultiLine::setDelimeter( std::string p_delimeter )
{
	this->mDelimeter = p_delimeter;
}

int TextMultiLine::getInterlineSize()
{
	return this->getSeperatorHeight();
}

void TextMultiLine::setInterlineSize( int p_size )
{
	this->setSeparatorHeight(p_size);
}


//******************************
// Methods
//******************************
void TextMultiLine::addLine( std::string p_text, bool p_notify )
{
	int contentWidth = this->getContentWidth(true);
	if(this->isAutoResizeWidth())
	{
		// Add text (auto resize)
		this->addLineTextBox(p_text, p_notify);
	}
	else if(contentWidth > WIDTH_MIN_FORADDLINE)
	{
		// Resize text
		bool textResized = false;
		int lastReziseIndex = 0;
		sf::Text tmpText;
		tmpText.setPosition(0, 0);
		tmpText.setFont(*this->mFont);
		tmpText.setCharacterSize(this->mFontSize);
		int tmpTextWidth = 0;

		do
		{
			// Init
			textResized = false;		
			std::string buffer = p_text.substr(lastReziseIndex, p_text.length() - lastReziseIndex);
			std::string bufferCopy = buffer;
			tmpText.setString(buffer);
			tmpTextWidth = tmpText.getLocalBounds().width;

			// If too long
			if(tmpTextWidth > contentWidth)
			{
				// First resize
				buffer = buffer.substr(0, ((float)contentWidth / (float)tmpTextWidth) * buffer.size());
				
				// Ajust (too long)
				tmpTextWidth = tmpText.getLocalBounds().width;
				while(tmpTextWidth > contentWidth && buffer != "")
				{
					buffer = buffer.substr(0, buffer.length() - 1);
					tmpText.setString(buffer);
					tmpTextWidth = tmpText.getLocalBounds().width,
					textResized = true;
				}

				// Check if last word doesnt truncat
				buffer = buffer.substr(0, buffer.find_last_of(' '));

				lastReziseIndex += buffer.length();
				textResized = true;				
			}

			// Remove first space (if exist)
			if(buffer.substr(0, 1) == " ")
				buffer = buffer.substr(1, buffer.size() - 1);

			// Add as TextBox
			if(buffer != "")
				this->addLineTextBox(buffer, p_notify);
		} while(textResized);
	}
}

void TextMultiLine::addLineBlank(bool p_notify)
{
	this->addLineTextBox("", p_notify);
}

void TextMultiLine::addLineTextBox( std::string p_text, bool p_notify )
{
	TextBox* tmpTextBox = new TextBox();
	tmpTextBox->setFont(this->mFont);
	tmpTextBox->setFontSize(this->mFontSize);
	tmpTextBox->setFontColor(this->mFontColor);
	tmpTextBox->setText(p_text);
	this->addItem(tmpTextBox, p_notify);
}

void TextMultiLine::updateLine()
{
	this->clear();
	if(this->getText() != "")
	{
		SplitString lines(this->getText(), this->getDelimeter());
		for(int i = 0; i < lines.getSplitCount(); i++)
		{
			this->addLine(lines.getSplitString(i), false);	
		}
	}
	this->notifyDataSetChanged();
}

void TextMultiLine::notifyTextChanged()
{
	this->updateLine();
}

void TextMultiLine::notifySizeChanged()
{
	List::notifySizeChanged();
	if(!this->isAutoResizeHeight() && !this->isAutoResizeWidth())
		this->updateLine();
}

void TextMultiLine::draw()
{
	if(this->isVisible())
	{
		List::draw();
	}	
}

void TextMultiLine::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		List::update(p_event);
	}
}



