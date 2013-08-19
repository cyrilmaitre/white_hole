#pragma once
#include "Resource.h"
#include "SpriteParameterFactory.h"
#include "Selectable.h"
#include "Button.h"
#include "TextBox.h"
#include "TextBoxMultiLine.h"


class Window: public Selectable
{
public:
	// Enum
	enum WindowType 
	{
		TypeDynamic = 0,
		TypeStaticLeft,
		TypeStaticRight
	};

	// Constructor - Destructor
	Window(void);
	~Window(void);

	// Getters - Setters  
	void setX(double p_x);
	void setY(double p_y);
	void setPositionMiddleScreen();

	void setContentWidth(double p_width);
	void setContentHeight(double p_height);

	double getContentX();
	double getContentY();
	double getContentWidth();
	double getContentHeight();

	WindowType getType();
	void setType(WindowType p_type);

	bool isOpen();
	void setOpen(bool p_open);

	bool isReduce();
	void setReduce(bool p_reduce);

	std::string getWindowTitle();
	void setWindowTitle(std::string p_windowTitle);

	void setWindowIcon(sf::Sprite p_windowIcon);

	// Methods
	virtual void notifyPositionChanged();
	virtual void notifySizeChanged();
	virtual void notifyOpenChanged();
	void notifyTypeChanged();
	void notifyReduceChanged();
	void updatePosition();
	void updateButton();
	void updateWindow();
	virtual void update(sf::Event p_event);
	virtual void update();
	void draw();
	virtual void drawContent() = 0;


private:
	// Attributs
	WindowType mType;
	bool mOpen;			// If false -> dont display it
	bool mReduce;		// If true -> dont display content

	TextBox mTitle;
	sf::Sprite mIcon;
	sf::RenderTexture mWindowTexture;
	sf::Sprite mWindow;

	Button mButtonReduce;
	Button mButtonClose;
	Button mButtonMove;

	// Methods
	void generateWindowTexture();
};

