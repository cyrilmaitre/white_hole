#include "ProgressBar.h"
#include "Manager.h"

//******************************
// Define
//******************************
#define DEFAULT_COLOR				sf::Color(255,255,0,0)
#define DEFAULT_BACKGROUNDCOLOR		sf::Color(240,240,240)
#define DEFAULT_BORDERCOLOR			sf::Color(210,210,210)
#define DEFAULT_BORDERSIZE			2
#define DEFAULT_BAR_COLOR			sf::Color(140,140,140)
#define DEFAULT_WIDTH				200
#define DEFAULT_HEIGHT				20
#define DEFAULT_FONTCOLOR			sf::Color(25,25,25)
#define DEFAULT_TITLE				"Progress Bar"
#define DEFAULT_VALUE				0
#define DEFAULT_VALUEMIN			0
#define DEFAULT_VALUEMAX			100


//******************************
// Constructor - Destructor
//******************************
ProgressBar::ProgressBar(void)
{
	this->setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	this->setBackgroundColor(DEFAULT_BACKGROUNDCOLOR, true);
	this->setBorderColor(DEFAULT_BORDERCOLOR, true);
	this->setBorderSize(DEFAULT_BORDERSIZE, true);
	this->setFontColor(DEFAULT_FONTCOLOR);

	this->mTitle = "";
	this->setTitle(DEFAULT_TITLE);

	this->mBarColor = DEFAULT_COLOR;
	this->setBarColor(DEFAULT_BAR_COLOR);

	this->mValueMin = -1;
	this->setValueMin(DEFAULT_VALUEMIN);

	this->mValueMax = -1;
	this->setValueMax(DEFAULT_VALUEMAX);

	this->mValue = -1;
	this->setValue(DEFAULT_VALUE);

	this->mMode = ProgressBarMode::ModeNone;
	this->setMode(ProgressBarMode::ModeValueMax);
}

ProgressBar::~ProgressBar(void)
{
}


//******************************
// Getters - Setters
//******************************
double ProgressBar::getValue()
{
	return this->mValue;
}

double ProgressBar::getValuePercent()
{
	return (this->getValue() - this->getValueMin()) / this->getValueMax();
}

void ProgressBar::setValue( double p_value )
{
	if(p_value < this->getValueMin())
		p_value = this->getValueMin();
	else if(p_value > this->getValueMax())
		p_value = this->getValueMax();

	if(this->mValue != p_value)
	{
		this->mValue = p_value;
		this->notifyValueChanged();
	}
}

double ProgressBar::getValueMin()
{
	return this->mValueMin;
}

void ProgressBar::setValueMin( double p_min )
{
	if(this->mValueMin != p_min)
	{
		this->mValueMin = p_min;
		this->setValue(this->mValue);
	}
}

double ProgressBar::getValueMax()
{
	return this->mValueMax;
}

void ProgressBar::setValueMax( double p_max )
{
	if(this->mValueMax != p_max)
	{
		this->mValueMax = p_max;
		this->setValue(this->mValue);
		this->notifyValueChanged();
	}
}

std::string ProgressBar::getTitle()
{
	return this->mTitle;
}

void ProgressBar::setTitle( std::string p_title )
{
	if(this->mTitle != p_title)
	{
		this->mTitle = p_title;
		this->updateText();
	}
}

ProgressBar::ProgressBarMode ProgressBar::getMode()
{
	return this->mMode;
}

void ProgressBar::setMode( ProgressBarMode p_mode )
{
	if(this->mMode != p_mode)
	{
		this->mMode = p_mode;
		this->updateText();
	}
}

sf::Color ProgressBar::getBarColor()
{
	return this->mBarColor;
}

void ProgressBar::setBarColor( sf::Color p_color )
{
	if(this->mBarColor != p_color)
	{
		this->mBarColor = p_color;
		this->mBar.setFillColor(this->mBarColor);
	}
}


//******************************
// Methods
//******************************
void ProgressBar::update( sf::Event myEvent )
{
	if(this->isVisible())
	{
		Block::update(myEvent);
	}
}

void ProgressBar::updatePosition()
{
	this->mBar.setPosition(this->getX(), this->getY());
	this->mText.setPosition(this->getX() + (this->getWidth() / 2) - (this->mText.getWidth() / 2), this->getY() + (this->getHeight() - this->mText.getHeight()) / 2);
}

void ProgressBar::updateBar()
{
	this->mBar.setSize(sf::Vector2f(this->getWidth() * this->getValuePercent(), this->getHeight()));	
	this->updatePosition();
}

void ProgressBar::updateText()
{
	switch(this->getMode())
	{
	case ProgressBarMode::ModeValueMax:
		this->mText.setText(Tools::formatNumber((long)this->getValue()) + " / " + Tools::formatNumber((long)this->getValueMax()));
		break;

	case ProgressBarMode::ModePercent:
		this->mText.setText(Tools::formatNumber(this->getValuePercent() * 100) + " %");
		break;

	case ProgressBarMode::ModeTitle:
		this->mText.setText(this->getTitle());
		break;

	case ProgressBarMode::ModeNone:
	default:
		this->mText.setText("");
		break;
	}
	this->updatePosition();
}

void ProgressBar::draw()
{
	if(this->isVisible())
	{
		Block::draw();

		Resource::resource->getApp()->draw(this->mBar);
		if(this->getMode() != ProgressBarMode::ModeNone)
			this->mText.draw();
	}
}

void ProgressBar::notifyFontChanged()
{
	Block::notifyFontChanged();
	this->mText.setFont(this->mFont);
	this->updatePosition();
}

void ProgressBar::notifyFontColorChanged()
{
	Block::notifyFontColorChanged(); 
	this->mText.setFontColor(this->mFontColor);
}	

void ProgressBar::notifyFontSizeChanged()
{
	Block::notifyFontSizeChanged();
	this->mText.setFontSize(this->mFontSize);
	this->updatePosition();
}

void ProgressBar::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->updateBar();
}

void ProgressBar::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->updatePosition();
}

void ProgressBar::notifyValueChanged()
{
	this->updateText();
	this->updateBar();
}



