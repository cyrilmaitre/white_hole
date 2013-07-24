#include "WindowSelectedEntity.h"
#include "Npc.h"


//*************************************************************
// Define
//*************************************************************
#define WINDOW_WIDTH			293
#define WINDOW_HEIGHT			88
#define TB_LABEL_LEVEL_X		200
#define LIFEBAR_OFFSETX			90
#define LIFEBAR_WIDTH			200
#define LIFEBAR_HEIGHT			14


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
WindowSelectedEntity::WindowSelectedEntity(Entity* p_entity)
{
	this->setContentWidth(WINDOW_WIDTH);
	this->setContentHeight(WINDOW_HEIGHT);

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i] = NULL;

	this->mTBName.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBName.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBName.setText(Resource::resource->getBundle()->getString("uigObjectSelectedObjectNameLabel"));

	this->mTBNameValue.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBNameValue.setFontSize(TB_LABEL_FONTSIZE);

	this->mTBLevel.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBLevel.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBLevel.setText(Resource::resource->getBundle()->getString("uigObjectSelectedObjectLevelLabel"));

	this->mTBLevelValue.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBLevelValue.setFontSize(TB_LABEL_FONTSIZE);

	this->mTBShield.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBShield.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBShield.setText(Resource::resource->getBundle()->getString("uigShipSmallShieldLabel"));

	this->mTBArmor.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBArmor.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBArmor.setText(Resource::resource->getBundle()->getString("uigShipSmallArmorLabel"));

	this->mTBStructure.setFontColor(TB_LABEL_FONTCOLOR);
	this->mTBStructure.setFontSize(TB_LABEL_FONTSIZE);
	this->mTBStructure.setText(Resource::resource->getBundle()->getString("uigShipSmallStructureLabel"));

	this->mLifeBars[0] = new LifeBar(NULL, LifeBar::LifeBarType::TypeShield);
	this->mLifeBars[0]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[1] = new LifeBar(NULL, LifeBar::LifeBarType::TypeArmor);
	this->mLifeBars[1]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	this->mLifeBars[2] = new LifeBar(NULL, LifeBar::LifeBarType::TypeStructure);
	this->mLifeBars[2]->setSize(LIFEBAR_WIDTH, LIFEBAR_HEIGHT);
	
	this->setWindowIcon(SpriteParameterFactory::getSpriteParameterIcon16X16()->getSprite(IC_16X16_PARAMETER));
	this->setEntity(p_entity);
	this->notifyPositionChanged();
}

WindowSelectedEntity::~WindowSelectedEntity(void)
{
	for(int i = 0; i < LIFEBAR_COUNT; i++)
		if(this->mLifeBars[i] != NULL)
			delete this->mLifeBars[i];
}


//*************************************************************
// Getters - Setters
//*************************************************************
Entity* WindowSelectedEntity::getEntity()
{
	return this->mEntity;
}

void WindowSelectedEntity::setEntity( Entity* p_entity )
{
	if(this->mEntity != p_entity)
	{
		this->mEntity = p_entity;
		this->notifyEntityChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WindowSelectedEntity::notifyPositionChanged()
{
	WindowSelected::notifyPositionChanged();
	this->updatePosition();
}

void WindowSelectedEntity::notifyEntityChanged()
{
	if(this->getEntity() != NULL)
	{
		// All type
		this->mTBNameValue.setText(this->getEntity()->getObjectTypeName());

		Npc* npcEntity = dynamic_cast<Npc*>(this->getEntity());
		if(npcEntity != 0)
		{
			// Npc
			this->setWindowTitle(this->getEntity()->getObjectTypeName() + " - " + npcEntity->getNpcType()->getName());
			this->mTBLevelValue.setText(Tools::buildStringWithInt(npcEntity->getLevel()));

			this->mTBLevel.setVisible(true);
			this->mTBLevelValue.setVisible(true);
		}
		else
		{
			// Entity
			this->setWindowTitle(this->getEntity()->getObjectTypeName());

			this->mTBLevel.setVisible(false);
			this->mTBLevelValue.setVisible(false);
		}

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->setDestructable(this->getEntity());
	}
}

void WindowSelectedEntity::update()
{
	if(this->isOpen() && !this->isReduce())
	{
		if(this->getEntity() != NULL)
		{
			for(int i = 0; i < LIFEBAR_COUNT; i++)
				this->mLifeBars[i]->update();		
		}
	}	
}

void WindowSelectedEntity::update( sf::Event p_event )
{
	if(this->isOpen() && !this->isReduce())
	{
		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->update(p_event);
	}
	WindowSelected::update(p_event);
}

void WindowSelectedEntity::updatePosition()
{
	this->mTBName.setX(this->getContentX());
	this->mTBName.setY(this->getContentY());	

	this->mTBNameValue.setX(this->mTBName.getRightX() + TB_VALUE_OFFSETX);
	this->mTBNameValue.setY(this->getContentY());

	this->mTBLevel.setX(this->getContentX() + TB_LABEL_LEVEL_X);
	this->mTBLevel.setY(this->getContentY());

	this->mTBLevelValue.setX(this->mTBLevel.getRightX() + TB_VALUE_OFFSETX);
	this->mTBLevelValue.setY(this->getContentY());

	this->mTBShield.setX(this->getContentX());
	this->mTBShield.setY(this->mTBName.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBArmor.setX(this->getContentX());
	this->mTBArmor.setY(this->mTBShield.getBottomY() + TB_LABEL_OFFSETY);	

	this->mTBStructure.setX(this->getContentX());
	this->mTBStructure.setY(this->mTBArmor.getBottomY() + TB_LABEL_OFFSETY);	

	for(int i = 0; i < LIFEBAR_COUNT; i++)
		this->mLifeBars[i]->setX(this->getContentX() + LIFEBAR_OFFSETX);
	this->mLifeBars[0]->setY(this->mTBShield.getY());
	this->mLifeBars[1]->setY(this->mTBArmor.getY());
	this->mLifeBars[2]->setY(this->mTBStructure.getY());
}

void WindowSelectedEntity::drawContent()
{
	if(this->isOpen() && !this->isReduce())
	{
		this->mTBName.draw();
		this->mTBNameValue.draw();
		this->mTBLevel.draw();
		this->mTBLevelValue.draw();
		this->mTBShield.draw();
		this->mTBArmor.draw();
		this->mTBStructure.draw();

		for(int i = 0; i < LIFEBAR_COUNT; i++)
			this->mLifeBars[i]->draw();
	}
}