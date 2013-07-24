#include "Window.h"
#include "Resource.h"
#include "SpriteParameterFactory.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define ICON_OFFSETX								3
#define ICON_OFFSETY								3
#define BUTTON_REDUCE_OFFSETX						-83		
#define BUTTON_CLOSE_OFFSETX						-56
#define BUTTON_MOVE_OFFSETX							-29
#define BUTTON_OFFSETY								1
#define BUTTON_WIDTH								28
#define BUTTON_HEIGHT								20
#define TITLE_OFFSETX								32
#define TITLE_OFFSETY								2
#define TITLE_FONTSIZE								ManagerConfig::FontSize::Medium
#define TITLE_FONTCOLOR								sf::Color(230, 200, 159)
#define BACKGROUND_SIZE								32
#define TOP_WIDTH									32
#define TOP_HEIGHT									22
#define TOP_RIGHT_WIDTH								4
#define LEFT_WIDTH									4
#define LEFT_HEIGHT									32
#define RIGHT_WIDTH									4
#define RIGHT_HEIGHT								32
#define BOTTOM_WIDTH								32
#define BOTTOM_HEIGHT								4
#define DEFAULT_PADDING								10
#define PADDING_LEFT								LEFT_WIDTH + DEFAULT_PADDING
#define PADDING_RIGHT								RIGHT_WIDTH + DEFAULT_PADDING
#define PADDING_TOP									TOP_HEIGHT + DEFAULT_PADDING
#define PADDING_BOTTOM								BOTTOM_HEIGHT + DEFAULT_PADDING


//*************************************************************
// Constructor - Destructor
//*************************************************************
Window::Window(void) 
{
	this->setMouseOverForced(true);

	this->mButtonReduce.setWidth(BUTTON_WIDTH);
	this->mButtonReduce.setHeight(BUTTON_HEIGHT);
	this->mButtonReduce.setBorderSize(0, true);
	this->mButtonReduce.setBackgroundImage(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(0, 0));
	this->mButtonReduce.setBackgroundImageOver(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(0, 1));
	this->mButtonReduce.setBackgroundImageFocus(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(0, 2));

	this->mButtonClose.setWidth(BUTTON_WIDTH);
	this->mButtonClose.setHeight(BUTTON_HEIGHT);
	this->mButtonClose.setBorderSize(0, true);
	this->mButtonClose.setBackgroundImage(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(1, 0));
	this->mButtonClose.setBackgroundImageOver(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(1, 1));
	this->mButtonClose.setBackgroundImageFocus(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(1, 2));

	this->mButtonMove.setWidth(BUTTON_WIDTH);
	this->mButtonMove.setHeight(BUTTON_HEIGHT);
	this->mButtonMove.setBorderSize(0, true);
	this->mButtonMove.setBackgroundImage(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(2, 0));
	this->mButtonMove.setBackgroundImageOver(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(2, 1));
	this->mButtonMove.setBackgroundImageFocus(SpriteParameterFactory::getSpriteParameterWindowButton()->getSpritePtr(2, 2));

	this->mTitle.setFontSize(TITLE_FONTSIZE);
	this->mTitle.setFontColor(TITLE_FONTCOLOR);

	// Init default
	this->setType(WindowType::TypeStaticLeft);

	this->setWindowTitle("Untitle");
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_HOME));

	this->setVisible(true);
	this->setOpen(false);
	this->setReduce(false);

	this->updatePosition();
	this->updateButton();
	this->generateWindowTexture();
}

Window::~Window(void)
{

}


//*************************************************************
// Getters - Setters
//*************************************************************
void Window::setX( double p_x )
{
	// Check
	if(p_x < 0)
		p_x = 0;
	else if(p_x + this->getWidth() > Resource::resource->getViewUi()->getSize().x)
		p_x = (int)Resource::resource->getViewUi()->getSize().x - this->getWidth();

	// Set
	Object::setX(p_x);
}

void Window::setY( double p_y )
{
	// Check
	if(p_y < 0)
		p_y = 0;
	else if(p_y + this->getHeight() > Resource::resource->getViewUi()->getSize().y)
		p_y = (int)Resource::resource->getViewUi()->getSize().y - this->getHeight();

	// Set
	Object::setY(p_y);
}

void Window::setPositionMiddleScreen()
{
	this->setX(Resource::resource->getViewUi()->getSize().x / 2 - this->getWidth() / 2);
	this->setY(Resource::resource->getViewUi()->getSize().y / 2 - this->getHeight() / 2);
}

void Window::setContentHeight( double p_height )
{
	this->setHeight(p_height + PADDING_TOP + PADDING_BOTTOM);
}

void Window::setContentWidth( double p_width )
{
	this->setWidth(p_width + PADDING_LEFT + PADDING_RIGHT);
}

double Window::getContentX()
{
	return this->getX() + PADDING_LEFT;
}

double Window::getContentY()
{
	return this->getY() + PADDING_TOP;
}

double Window::getContentWidth()
{
	return this->getWidth() - PADDING_LEFT - PADDING_RIGHT;
}

double Window::getContentHeight()
{
	return this->getHeight() - PADDING_TOP - PADDING_BOTTOM;
}

Window::WindowType Window::getType()
{
	return this->mType;
}

void Window::setType( WindowType p_type )
{
	this->mType = p_type;
	this->notifyTypeChanged();
}

bool Window::isOpen()
{
	return this->mOpen;
}

void Window::setOpen( bool p_open )
{
	this->mOpen = p_open;
	this->notifyOpenChanged();
}

bool Window::isReduce()
{
	return this->mReduce;
}

void Window::setReduce( bool p_reduce )
{
	this->mReduce = p_reduce;
	this->notifyReduceChanged();
}

std::string Window::getWindowTitle()
{
	return this->mTitle.getText();
}

void Window::setWindowTitle( std::string p_windowTitle )
{
	this->mTitle.setText(p_windowTitle);
}

void Window::setWindowIcon( sf::Sprite p_windowIcon )
{
	this->mIcon = p_windowIcon;
	this->updatePosition();
}


//*************************************************************
// Methode
//*************************************************************
void Window::notifySizeChanged()
{
	Selectable::notifySizeChanged();
	if(this->getWidth() > 0 && this->getHeight() > 0)
	{
		this->generateWindowTexture();
		this->updatePosition();
	}
}

void Window::notifyPositionChanged()
{
	Selectable::notifyPositionChanged();
	this->updatePosition();	
}

void Window::notifyTypeChanged()
{
	this->updateButton();
}

void Window::notifyOpenChanged()
{
	this->updateButton();
}

void Window::notifyReduceChanged()
{
	this->updateWindow();
}

void Window::updateButton()
{
	if(this->isOpen() && this->getType() == WindowType::TypeDynamic)
	{
		this->mButtonReduce.setVisible(true);
		this->mButtonClose.setVisible(true);
		this->mButtonMove.setVisible(true);
	}
	else
	{
		this->mButtonReduce.setVisible(false);
		this->mButtonClose.setVisible(false);
		this->mButtonMove.setVisible(false);	
	}
}

void Window::updatePosition()
{
	this->mWindow.setPosition(this->getX(), this->getY());

	this->mIcon.setPosition(this->getX() + ICON_OFFSETX, this->getY() + ICON_OFFSETY);

	this->mButtonReduce.setX(this->getX() + this->getWidth() + BUTTON_REDUCE_OFFSETX);
	this->mButtonReduce.setY(this->getY() + BUTTON_OFFSETY);

	this->mButtonClose.setX(this->getX() + this->getWidth() + BUTTON_CLOSE_OFFSETX);
	this->mButtonClose.setY(this->getY() + BUTTON_OFFSETY);

	this->mButtonMove.setX(this->getX() + this->getWidth() + BUTTON_MOVE_OFFSETX);
	this->mButtonMove.setY(this->getY() + BUTTON_OFFSETY);

	this->mTitle.setX(this->getX() + TITLE_OFFSETX);
	this->mTitle.setY(this->getY() + TITLE_OFFSETY);
}

void Window::updateWindow()
{
	if(this->isReduce())
		this->mWindow.setTextureRect(sf::IntRect(0, 0, this->getWidth(), TOP_HEIGHT));
	else
		this->mWindow.setTextureRect(sf::IntRect(0, 0, this->getWidth(), this->getHeight()));
}

void Window::update(sf::Event p_event)
{
	if(this->getType() == WindowType::TypeDynamic)
	{
		if(this->isOpen())
		{
			this->mButtonClose.update(p_event);
			this->mButtonMove.update(p_event);
			this->mButtonReduce.update(p_event);

			if(this->mButtonMove.hasFocus())
			{
				sf::Vector2i mousePosition = EventManager::eventManager->getMousePositionUiLocal();
				this->setX(mousePosition.x - this->getWidth() - BUTTON_MOVE_OFFSETX - this->mButtonMove.getFocusOriginLocalX());
				this->setY(mousePosition.y + BUTTON_OFFSETY - this->mButtonMove.getFocusOriginLocalY());
			}

			if(this->mButtonClose.isClicked())
				this->setOpen(false);

			if(this->mButtonReduce.isClicked())
				this->setReduce(!this->isReduce());

			Selectable::update(p_event);
		}
	}
}

void Window::update()
{

}

void Window::draw()
{
	if(this->isOpen())
	{
		Resource::resource->getApp()->draw(this->mWindow);
		Resource::resource->getApp()->draw(this->mIcon);

		this->mTitle.draw();
		this->mButtonReduce.draw();
		this->mButtonClose.draw();
		this->mButtonMove.draw();

		if(!this->isReduce())
			this->drawContent();		
	}
}

void Window::generateWindowTexture()
{
	this->mWindowTexture.create(this->getWidth(), this->getHeight());
	this->mWindowTexture.clear(sf::Color(255, 0, 0));

	// Draw Background
	int backgroundColumn = ceil((float)this->getWidth() / BACKGROUND_SIZE);
	int backgroundLine = ceil((float)this->getHeight() / BACKGROUND_SIZE);
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(*Resource::resource->getTexture(IMG_WINDOW_BACKGROUND), true);
	for(int i = 0; i < backgroundColumn; i ++)
	{
		for(int j = 0; j < backgroundLine; j++)
		{
			spriteBackground.setPosition(i * BACKGROUND_SIZE, j * BACKGROUND_SIZE);
			this->mWindowTexture.draw(spriteBackground);
		}
	}

	// Draw Bottom
	int bottomColumn = (this->getWidth() - LEFT_WIDTH - RIGHT_WIDTH) / BOTTOM_WIDTH;
	sf::Sprite spriteBottom;
	spriteBottom.setTexture(*Resource::resource->getTexture(IMG_WINDOW_BOTTOM), true);
	for(int i = 0; i < bottomColumn; i++)
	{
		spriteBottom.setPosition(LEFT_WIDTH + i * BOTTOM_WIDTH, this->getHeight() - BOTTOM_HEIGHT);
		this->mWindowTexture.draw(spriteBottom);
	}
	spriteBottom.setPosition(this->getWidth() - RIGHT_WIDTH - BOTTOM_WIDTH, this->getHeight() - BOTTOM_HEIGHT);
	this->mWindowTexture.draw(spriteBottom);

	// Left
	int leftLine = (this->getHeight() - BOTTOM_HEIGHT) / LEFT_HEIGHT;
	sf::Sprite spriteLeft;
	spriteLeft.setTexture(*Resource::resource->getTexture(IMG_WINDOW_LEFT), true);
	for(int i = 0; i < leftLine; i++)
	{
		spriteLeft.setPosition(0, i * LEFT_HEIGHT);
		this->mWindowTexture.draw(spriteLeft);
	}
	spriteLeft.setPosition(0, this->getHeight() - BOTTOM_HEIGHT - LEFT_HEIGHT);
	this->mWindowTexture.draw(spriteLeft);

	// Right
	int rightLine = (this->getHeight() - BOTTOM_HEIGHT) / RIGHT_HEIGHT;
	sf::Sprite spriteRight;
	spriteRight.setTexture(*Resource::resource->getTexture(IMG_WINDOW_RIGHT), true);
	for(int i = 0; i < rightLine; i++)
	{
		spriteRight.setPosition(this->getWidth() - RIGHT_WIDTH, i * RIGHT_HEIGHT);
		this->mWindowTexture.draw(spriteRight);
	}
	spriteRight.setPosition(this->getWidth() - RIGHT_WIDTH, this->getHeight() - BOTTOM_HEIGHT - RIGHT_HEIGHT);
	this->mWindowTexture.draw(spriteRight);

	// Draw Top
	int topColumn = ceil((float)this->getWidth() / TOP_WIDTH);
	sf::Sprite spriteTop;
	spriteTop.setTexture(*Resource::resource->getTexture(IMG_WINDOW_TOP), true);
	for(int i = 0; i < topColumn; i++)
	{
		spriteTop.setPosition(i * TOP_WIDTH, 0);
		this->mWindowTexture.draw(spriteTop);
	}

	spriteTop.setTexture(*Resource::resource->getTexture(IMG_WINDOW_TOPLEFT), true);
	spriteTop.setPosition(0, 0);
	this->mWindowTexture.draw(spriteTop);

	spriteTop.setTexture(*Resource::resource->getTexture(IMG_WINDOW_TOPRIGHT), true);
	spriteTop.setPosition(this->getWidth() - TOP_RIGHT_WIDTH, 0);
	this->mWindowTexture.draw(spriteTop);

	// Save
	this->mWindowTexture.display();
	this->mWindow.setTexture(this->mWindowTexture.getTexture(), true);
	this->updateWindow();
}




