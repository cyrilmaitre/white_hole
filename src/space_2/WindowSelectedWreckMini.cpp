#include "WindowSelectedWreckMini.h"

//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH			293
#define WINDOW_HEIGHT			120
#define TB_LABEL_LEVEL_X		200
#define LIFEBAR_OFFSETX			90
#define LIFEBAR_WIDTH			200
#define LIFEBAR_HEIGHT			14
#define BUTTON_WIDTH			80
#define BUTTON_HEIGHT			18
#define BUTTON_OFFSETX			10
#define BUTTON_OFFSETY			15


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelectedWreckMini::WindowSelectedWreckMini(WreckMini* p_wreck)
{
	this->mWreckMini = NULL;
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i] = NULL;

	this->mTBName.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBName.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBName.setText(Resource::resource->getBundle()->getString("uigObjectSelectedObjectNameLabel"));

	this->mTBNameValue.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBNameValue.setFontSize(TB_LABEL_FONTSIZE);

	this->mTBShield.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBShield.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBShield.setText(Resource::resource->getBundle()->getString("uigShipSmallShieldLabel"));

	this->mTBArmor.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBArmor.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBArmor.setText(Resource::resource->getBundle()->getString("uigShipSmallArmorLabel"));

	this->mTBStructure.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBStructure.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBStructure.setText(Resource::resource->getBundle()->getString("uigShipSmallStructureLabel"));

	this->mButtonRecycle.setWidth(BUTTON_WIDTH);
	this->mButtonRecycle.setHeight(BUTTON_HEIGHT);
	this->mButtonRecycle.setTitle(Resource::resource->getBundle()->getString("recycle"));

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);

	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));
	this->setWreckMini(p_wreck);
	this->notifyPositionChanged();
}

WindowSelectedWreckMini::~WindowSelectedWreckMini(void)
{
	for(int i = 0; i < LIFEBAR_COUNT; i++)
		if(this->mLifeBars[i] != NULL)
			delete this->mLifeBars[i];
}


//*************************************************************
// Getters - Setters
//*************************************************************
WreckMini* WindowSelectedWreckMini::getWreckMini()
{
	return this->mWreckMini;
}

void WindowSelectedWreckMini::setWreckMini( WreckMini* p_wreck )
{
	if(this->mWreckMini != p_wreck)
	{
		this->mWreckMini = p_wreck;
		this->notifyWreckMiniChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelectedWreckMini::notifyPositionChanged()
{
	WindowSelected::notifyPositionChanged();
	this->updatePosition();
}

void WindowSelectedWreckMini::notifyWreckMiniChanged()
{
	if(this->getWreckMini() != NULL)
	{
		this->setWindowTitle(Resource::resource->getBundle()->getString("uigObjectSelectedTitleWreckMini"));
		this->mTBNameValue.setText(Resource::resource->getBundle()->getString("uigObjectSelectedTitleWreckMini"));

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getWreckMini());
	}
}

void WindowSelectedWreckMini::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->getWreckMini() != NULL)
		{
			for(int i = 0; i < LIFEBAR_COUNT; i++)
				this->mLifeBars[i]->update();	
		}
	}
}

void WindowSelectedWreckMini::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);

		this->mButtonRecycle.update(p_event);
		if(this->mButtonRecycle.isClicked())
			this->recycleWreckMini();
	}

	WindowSelected::update(p_event);	
}

void WindowSelectedWreckMini::updatePosition()
{
	this->mTBName.setX(this->getContentX());
	this->mTBName.setY(this->getContentY());	

	this->mTBNameValue.setX(this->mTBName.getRightX() + TB_VALUE_OFFSETX);
	this->mTBNameValue.setY(this->getContentY());

	this->mTBShield.setX(this->getContentX());
	this->mTBShield.setY(this->mTBName.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBArmor.setX(this->getContentX());
	this->mTBArmor.setY(this->mTBShield.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBStructure.setX(this->getContentX());
	this->mTBStructure.setY(this->mTBArmor.getBottomY() + TB_LABEL_OFFSETY);	

	this->mButtonRecycle.setX(this->getContentX());
	this->mButtonRecycle.setY(this->mTBStructure.getBottomY() + BUTTON_OFFSETY);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShield.getY());
	this->mLifeBars[1]->setY(this->mTBArmor.getY());
	this->mLifeBars[2]->setY(this->mTBStructure.getY());
}

void WindowSelectedWreckMini::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mTBName.draw();
		this->mTBNameValue.draw();
		this->mTBShield.draw();
		this->mTBArmor.draw();
		this->mTBStructure.draw();
		this->mButtonRecycle.draw();

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}

void WindowSelectedWreckMini::recycleWreckMini()
{

}
