#include "WindowMap.h"
#include "Game.h"


//*************************************************************
// Define
//*************************************************************
#define POSITION_X				0		
#define WINDOW_Y				0
#define MAPVIEW_WIDTH			300		// 1600		// Max Width
#define MAPVIEW_HEIGHT			300		// 800		// Max Height
#define PANELRIGHT_WIDTH		50
#define ZOOM_LEVEL_DEFAULT		0
#define ZOOM_LEVEL_MIN			0
#define ZOOM_LEVEL_MAX			10
#define BUTTON_WIDTH			32
#define BUTTON_HEIGHT			32
#define BUTTON_OFFSETX			10
#define BUTTON_OFFSETY			10
#define TB_OFFSETX				10
#define TB_OFFSETY				10
#define TB_FONTSIZE				12
#define TB_FONTCOLOR			sf::Color(255, 255, 255)


//*************************************************************
// Constructor - Destructor
//*************************************************************
WindowMap::WindowMap(void)
{
	this->setX(POSITION_X);
	this->setY(WINDOW_Y);
	this->setContentWidth(MAPVIEW_WIDTH + PANELRIGHT_WIDTH);
	this->setContentHeight(MAPVIEW_HEIGHT);
	this->setType(Window::WindowType::TypeDynamic);
	this->setOpen(false);
	this->setWindowTitle(Resource::resource->getBundle()->getString("miniMapWindowTitle"));
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_CURSOR));

	this->mMapView = new MapMiniView();
	this->mMapView->setMap(Game::game->getMap());
	this->mMapView->setSize(MAPVIEW_WIDTH, MAPVIEW_HEIGHT);
	
	this->mZoomLevels.push_back(1.f);		// 0	
	this->mZoomLevels.push_back(0.8);		// 1
	this->mZoomLevels.push_back(0.6);		// 2
	this->mZoomLevels.push_back(0.4);		// 3
	this->mZoomLevels.push_back(0.3);		// 4
	this->mZoomLevels.push_back(0.2);		// 5
	this->mZoomLevels.push_back(0.1);		// 6
	this->mZoomLevels.push_back(0.05);		// 7
	this->mZoomLevels.push_back(0.025);		// 8
	this->mZoomLevels.push_back(0.01);		// 9
	this->mZoomLevels.push_back(0.005);		// 10	
	this->setZoomLevel(ZOOM_LEVEL_DEFAULT);

	this->mButtonZoom.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonZoom.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_ADD), true);

	this->mButtonDezoom.setSize(BUTTON_WIDTH, BUTTON_HEIGHT);
	this->mButtonDezoom.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon16X16(true)->getSpritePtr(IC_16X16_SUB), true);

	this->mTBZoom.setFontColor(TB_FONTCOLOR);
	this->mTBZoom.setFontSize(TB_FONTSIZE);

	this->notifyPositionChanged();
}

WindowMap::~WindowMap(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MapMiniView* WindowMap::getMapView()
{
	return this->mMapView;
}

int WindowMap::getZoomLevel()
{
	return this->mZoomLevel;
}

void WindowMap::setZoomLevel( int p_level )
{
	if(p_level < ZOOM_LEVEL_MIN)
		p_level = ZOOM_LEVEL_MIN;
	else if(p_level > ZOOM_LEVEL_MAX)
		p_level = ZOOM_LEVEL_MAX;

	this->mZoomLevel = p_level;
	this->mMapView->setZoom(this->mZoomLevels[this->mZoomLevel]);
	this->mTBZoom.setText("x " + Tools::buildStringWithFloat(this->mMapView->getZoom()));
}


//*************************************************************
// Methods
//*************************************************************
void WindowMap::notifyPositionChanged()
{
	Window::notifyPositionChanged();
	this->mMapView->setPosition(this->getContentX(), this->getContentY());
	this->mButtonZoom.setPosition(	this->mMapView->getX() + this->mMapView->Object::getWidth() + BUTTON_OFFSETX,
									this->getContentY());
	this->mButtonDezoom.setPosition(this->mButtonZoom.getX(),
									this->mButtonZoom.getBottomY() + BUTTON_OFFSETY);
	this->mTBZoom.setPosition(	this->mMapView->getX() + this->mMapView->Object::getWidth() + TB_OFFSETX,
								this->mButtonDezoom.getBottomY() + TB_OFFSETY);
}

void WindowMap::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mMapView->update();

		this->mButtonZoom.setEnable(this->getZoomLevel() > ZOOM_LEVEL_MIN);
		this->mButtonDezoom.setEnable(this->getZoomLevel() < ZOOM_LEVEL_MAX);
	}
}

void WindowMap::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mButtonZoom.update(p_event);
		this->mButtonDezoom.update(p_event);

		if(this->mButtonZoom.isClicked())
			this->decZoomLevel();

		if(this->mButtonDezoom.isClicked())
			this->incZoomLevel();
	}
	Window::update(p_event);
}

void WindowMap::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mMapView->draw();
		this->mButtonZoom.draw();
		this->mButtonDezoom.draw();
		this->mTBZoom.draw();
	}
}

void WindowMap::incZoomLevel()
{
	this->setZoomLevel(this->getZoomLevel() + 1);
}

void WindowMap::decZoomLevel()
{
	this->setZoomLevel(this->getZoomLevel() - 1);
}

