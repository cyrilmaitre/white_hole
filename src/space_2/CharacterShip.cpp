#include "CharacterShip.h"
#include "Option.h"
#include "Camera.h"
#include "LevelManager.h"
#include "ShipModelFactory.h"
#include "FactoryGet.h"
#include "Weapon.h"
#include "Game.h"
#include "ToolsMap.h"
#include "ToolsImage.h"


//*************************************************************
// Define
//*************************************************************
#define NPCTYPE_ID		1


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShip::CharacterShip( Json::Value json, Character *p_character ): Ship(0, 0), Containerable(ContainerStack::ContainerStackType::TypeCharacterShip)
{
	this->setCharacter(p_character);
	this->loadFromJson(json);
	this->setObjectType(MapObjectType::TypeCharacterShip);
	this->setNpcType(FactoryGet::getNpcTypeFactory()->getNpcType(NPCTYPE_ID));

	this->mArrowObjectSelected = NULL;
	this->mArrowObjectSelected = SpriteParameterFactory::getSpriteParameterIcon32X32()->getSpritePtr(IC_32X32_ARROW);
	ToolsImage::setSpriteOriginCenter(this->mArrowObjectSelected);
}

CharacterShip::~CharacterShip(void)
{
	if(this->mArrowObjectSelected != NULL)
		delete this->mArrowObjectSelected;
}


//*************************************************************
// Getters - Setters
//*************************************************************
void CharacterShip::setX( double p_x )
{
	Object::setX(p_x);
	Camera::camera->setCameraX(p_x);
}

void CharacterShip::setY( double p_y )
{
	Object::setY(p_y);
	Camera::camera->setCameraY(p_y);
}

bool CharacterShip::isPiloted()
{
	return this->mPiloted;
}

void CharacterShip::setPiloted(bool p_piloted)
{
	this->mPiloted = p_piloted;
}

NpcType* CharacterShip::getNpcType()
{
	return this->mNpcType;
}

void CharacterShip::setNpcType( NpcType* p_type )
{
	this->mNpcType = p_type;
}

Character* CharacterShip::getCharacter()
{
	return this->mCharacter;
}

void CharacterShip::setCharacter( Character *p_character )
{
	this->mCharacter = p_character;
}


//*************************************************************
// Method
//*************************************************************
void CharacterShip::draw()
{
	Ship::draw();
	this->drawArrowObjectSelected();
}

void CharacterShip::drawArrowObjectSelected()
{
	if(Game::game->getMap()->getMapObjectSelector()->hasObjectSelected() && Game::game->getMap()->getMapObjectSelector()->isObjectSelectedOutOfScreen())
		Resource::resource->getApp()->draw(*this->mArrowObjectSelected);
}

void CharacterShip::update( sf::Event p_event )
{
	Ship::update(p_event);
}

void CharacterShip::update()
{
	Ship::update();
	this->updateRotation();
}

void CharacterShip::updatePosition()
{
	float varX = this->getMoveX();
	float varY = this->getMoveY();

	Camera::frameShipMoveOffset.x = varX; 
	Camera::frameShipMoveOffset.y = varY; 

	this->setX(this->Object::getX() + varX);
	this->setY(this->Object::getY() + varY);
}

void CharacterShip::updateQuickeningActive()
{
	bool keyUpPressed = sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_UP_KEY));
	bool keyRightPressed = sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_RIGHT_KEY));
	bool keyDownPressed = sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_DOWN_KEY));
	bool keyLeftPressed = sf::Keyboard::isKeyPressed(Option::option->getAppControl(OPTION_APP_CONTROL_LEFT_KEY));
	
	this->setQuickeningActiveAt(MovableCardinality::North, keyUpPressed && !keyRightPressed && !keyLeftPressed);
	this->setQuickeningActiveAt(MovableCardinality::NorthEast, keyUpPressed && keyRightPressed );
	this->setQuickeningActiveAt(MovableCardinality::East, keyRightPressed && !keyUpPressed && !keyDownPressed);
	this->setQuickeningActiveAt(MovableCardinality::SouthEast, keyDownPressed && keyRightPressed);
	this->setQuickeningActiveAt(MovableCardinality::South, keyDownPressed && !keyRightPressed && !keyLeftPressed);
	this->setQuickeningActiveAt(MovableCardinality::SouthWest, keyDownPressed && keyLeftPressed);
	this->setQuickeningActiveAt(MovableCardinality::West, keyLeftPressed && !keyUpPressed && !keyDownPressed);
	this->setQuickeningActiveAt(MovableCardinality::NorthWest, keyUpPressed && keyLeftPressed);
}

void CharacterShip::updateSprite()
{
	Ship::updateSprite();
	if(Game::game->getMap() != NULL && Game::game->getMap()->getMapObjectSelector()->hasObjectSelected())
	{
		float angle = ToolsMap::getAngleAbsolute(this, Game::game->getMap()->getMapObjectSelector()->getSelectedMapObject());
		this->mArrowObjectSelected->setPosition(this->getScreenX() + (this->getRadius() * 2 * cos(Tools::degreeToRadian(angle + 270))), 
												this->getScreenY() + (this->getRadius() * 2 * sin(Tools::degreeToRadian(angle + 270))));
		this->mArrowObjectSelected->setRotation(angle - 90);
	}
}

void CharacterShip::updateRotation()
{
	sf::View* appView = Resource::resource->getViewMap(this->getPlane());
	float appCenterX = appView->getCenter().x;
	float appCenterY = appView->getCenter().y;
	sf::Vector2f mousePosition = EventManager::eventManager->getMousePositionMapLocal(this->getPlane());

	float angle = Tools::getAngle(appCenterX, appCenterY, mousePosition.x, mousePosition.y);
	this->setRotationTarget(angle);
}

void CharacterShip::loadFromJson( Json::Value json )
{
	this->setId(json.get(CHARACTERSHIP_JSON_IDCHARACTERSHIP, -1).asInt());
	this->setLevel(json.get(CHARACTERSHIP_JSON_LEVEL, 0).asInt());
	this->setExperience(json.get(CHARACTERSHIP_JSON_EXPERIENCE, 0).asInt());
	this->setPiloted(json.get(CHARACTERSHIP_JSON_PILOTED, false).asBool());
	this->setShipModel(FactoryGet::getShipModelFactory()->getShipModel(json.get(CHARACTERSHIP_JSON_IDSHIPMODEL, 0).asInt()));
	
	// Weapons
	Json::Value weapons = json.get(CHARACTERSHIP_JSON_WEAPONS, NULL);
	if(weapons != NULL)
	{
		for(int i = 0; i < weapons.size(); i++)
			this->addWeapon(new Weapon(weapons.get(i, NULL), this));
	}

	// ItemStacks
	Json::Value itemStacks = json.get(CHARACTERSHIP_JSON_ITEMSTACKS, NULL);
	if(itemStacks != NULL)
	{
		for(int i = 0; i < itemStacks.size(); i++)
		{
			Json::Value currentItemStack = itemStacks.get(i, NULL);
			ItemStack* currentStack = new ItemStack(currentItemStack.get(CHARACTERSHIP_JSON_ITEMSTACK, NULL));
			this->addItemStack(currentStack, currentItemStack.get(CHARACTERSHIP_JSON_ITEMSTACKPOSITION, 0).asInt());
		}
	}
}

Json::Value CharacterShip::saveToJson()
{
	Json::Value json;
	json[CHARACTERSHIP_JSON_IDCHARACTERSHIP] = this->getId();
	json[CHARACTERSHIP_JSON_LEVEL] = this->getLevel();
	json[CHARACTERSHIP_JSON_EXPERIENCE] = this->getExperience();
	json[CHARACTERSHIP_JSON_PILOTED] = this->isPiloted();
	json[CHARACTERSHIP_JSON_IDSHIPMODEL] = this->getShipModel()->MapObjectModel::getId();
	json[CHARACTERSHIP_JSON_IDCHARACTER] = this->getCharacter()->getId();
	return json;
}

void CharacterShip::loadFromShipModel()
{
	Ship::loadFromShipModel();

	if(this->getShipModel() != NULL)
	{
		this->setCargoMax(this->mShipModel->getCargoMax());
	}
}


