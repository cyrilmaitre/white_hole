#include "MapObjectSelector.h"
#include "Game.h"
#include "ToolsMap.h"


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
MapObjectSelector::MapObjectSelector(void)
{
	this->mMapObjectSelectable.setSelectionCanBeNull(true);
	this->mObjectSelectedOutOfScreen = false;
}

MapObjectSelector::~MapObjectSelector(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
MapObject* MapObjectSelector::getSelectedMapObject()
{
	Selectable* selected = this->mMapObjectSelectable.getSelection();
	if(selected != NULL)
		return (MapObject*)selected;
	else
		return NULL;
}

double MapObjectSelector::getObjectSelectedDistance()
{
	if(this->getSelectedMapObject() != NULL)
		return this->mObjectSelectedDistance;
	else
		return 0;
}

void MapObjectSelector::setObjectSelectedDistance( double p_distance )
{
	this->mObjectSelectedDistance = p_distance;
}

float MapObjectSelector::getObjectSelectedAngle()
{
	if(this->getSelectedMapObject() != NULL)
		return this->mObjectSelectedAngle;
	else
		return 0;
}

void MapObjectSelector::setObjectSelectedAngle( float p_angle )
{
	this->mObjectSelectedAngle = p_angle;
}

bool MapObjectSelector::isObjectSelectedOutOfScreen()
{
	return this->mObjectSelectedOutOfScreen;
}

bool MapObjectSelector::hasObjectSelected()
{
	return this->getSelectedMapObject() != NULL;
}


//*************************************************************
// Methods
//*************************************************************
void MapObjectSelector::update()
{
	if(this->mMapObjectSelectable.isSelectionChanged())
	{
		if(this->mMapObjectSelectable.getSelection() != NULL)
		{
			MapObject* selectedObject = (MapObject*)this->mMapObjectSelectable.getSelection();
			Entity* selectedEntity = dynamic_cast<Entity*>(selectedObject);
			bool windowEntity = true;

			switch(selectedObject->getObjectType())
			{
			case MapObject::MapObjectType::TypeCharacterShip: 
				Game::game->getUserInterface()->getWindowSelectedCharacterShip()->setCharacterShip((CharacterShip*)selectedObject);
				Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedCharacterShip());
				windowEntity = false;
				break;

			case MapObject::MapObjectType::TypeNpcShip:
				Game::game->getUserInterface()->getWindowSelectedNpcShip()->setNpcShip((NpcShip*)selectedObject);
				Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedNpcShip());
				windowEntity = false;
				break;

			case MapObject::MapObjectType::TypeWreck:
				Game::game->getUserInterface()->getWindowSelectedWreck()->setWreck((Wreck*)selectedObject);
				Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedWreck());
				windowEntity = false;
				break;

			case MapObject::MapObjectType::TypeWreckMini:
				Game::game->getUserInterface()->getWindowSelectedWreckMini()->setWreckMini((WreckMini*)selectedObject);
				Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedWreckMini());
				windowEntity = false;
				break;

			case MapObject::MapObjectType::TypeStation:
				Game::game->getUserInterface()->getWindowSelectedStation()->setStation((Station*)selectedObject);
				Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedStation());
				windowEntity = false;
				break;
			}

			if(selectedEntity != 0)
			{
				if(windowEntity)
				{
					Game::game->getUserInterface()->getWindowSelectedEntity()->setEntity(selectedEntity);
					Game::game->getUserInterface()->setWindowSelected(Game::game->getUserInterface()->getWindowSelectedEntity());
				}
				Game::game->getShipPiloted()->getTarget()->setEntity(selectedEntity);
			}
		}
		else
		{
			Game::game->getUserInterface()->setWindowSelected(NULL);
			Game::game->getShipPiloted()->getTarget()->setEntity(NULL);
		}
	}

	if(this->getSelectedMapObject() != NULL)
	{
		this->updateAngle();
		this->updateDistance();
		this->updateOutOfScreen();
	}
}

void MapObjectSelector::updateDistance()
{
	this->setObjectSelectedDistance(ToolsMap::getDistance(Game::game->getShipPiloted(), this->getSelectedMapObject()));
}

void MapObjectSelector::updateAngle()
{
	this->setObjectSelectedAngle(ToolsMap::getAngle(Game::game->getShipPiloted(), this->getSelectedMapObject()));
}

void MapObjectSelector::updateOutOfScreen()
{
	this->mObjectSelectedOutOfScreen =	Tools::getAbsolute(Game::game->getShipPiloted()->getX(MAPOBJECT_PLANE_1) - this->getSelectedMapObject()->getX(MAPOBJECT_PLANE_1)) > Resource::resource->getViewMap(MAPOBJECT_PLANE_1)->getSize().x / 2 ||
										Tools::getAbsolute(Game::game->getShipPiloted()->getY(MAPOBJECT_PLANE_1) - this->getSelectedMapObject()->getY(MAPOBJECT_PLANE_1)) > Resource::resource->getViewMap(MAPOBJECT_PLANE_1)->getSize().y / 2;
}

void MapObjectSelector::unselect()
{	
	this->mMapObjectSelectable.unselectAll();
}

void MapObjectSelector::addMapObject( MapObject* p_object )
{
	if(p_object != NULL)
	{
		this->mMapObjectSelectable.addSelectable(p_object);
	}
}

void MapObjectSelector::removeMapObject( MapObject* p_object )
{
	if(p_object != NULL)
	{
		this->mMapObjectSelectable.removeSelectable(p_object);
	}
}





