#include "SpriteParameterFactory.h"
#include "Resource.h"
#include "SpriteParameter.h"
#include "Tools.h"


//*************************************************************
// Init static
//*************************************************************
std::map<std::string, SpriteParameter*> SpriteParameterFactory::loadedSpriteParameters;


//*************************************************************
// Constructor - Destructor // Singleton
//*************************************************************
SpriteParameterFactory::SpriteParameterFactory(void)
{
}

SpriteParameterFactory::~SpriteParameterFactory(void)
{
}


//*************************************************************
// Methods
//*************************************************************
SpriteParameter* SpriteParameterFactory::getSpriteParameterWindowButton( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAMEWINDOW_BUTTON, 3, 3, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterIcon16X16( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAME_ICON16X16, 10, 10, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterIcon10X10( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAME_ICON10X10, 10, 10, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterIcon32X32( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAME_ICON32X32, 10, 10, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterIcon48X48( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAME_ICON48X48, 10, 10, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterIcon64X64( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_UIGAME_ICON64X64, 10, 10, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterSpaceBackground( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_SPACE_BACKGROUND, 10, 4, useLoaded );
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterScrollbar( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_SCROLLBAR, 6, 8, useLoaded );	
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterRace( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_RACE, 2, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterAvatar( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_AVATAR, 10, 2, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterJob( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_JOB, 4, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterSkill( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_SKILL, 9, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterItems( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_ITEMS, 16, 20, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterImpactLaser( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_IMPACT_LASER, 12, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterLoadingSquareCircle( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_LOADING_SQUARE_CIRCLE, 8, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameterImpactExplosion( bool useLoaded )
{
	return SpriteParameterFactory::getSpriteParameter(SP_ID_IMPACT_EXPLOSION, 12, 1, useLoaded);
}

SpriteParameter* SpriteParameterFactory::getSpriteParameter( std::string id, int spriteColumn, int spriteLine, bool useLoaded )
{
	SpriteParameter* tmpSpriteParameter = NULL;

	if(useLoaded)
		tmpSpriteParameter = getLoadedSpriteParameter(id);

	if(tmpSpriteParameter != NULL)
	{
		return tmpSpriteParameter;
	}
	else
	{
		tmpSpriteParameter = new SpriteParameter(Resource::resource->getTexture(id), spriteColumn, spriteLine);

		if(useLoaded)
			addLoadedSpriteParameters(id, tmpSpriteParameter);

		return tmpSpriteParameter;
	}

	return NULL;
}

void SpriteParameterFactory::addLoadedSpriteParameters( std::string id, SpriteParameter* loadedSpriteParameter )
{
	if(SpriteParameterFactory::getLoadedSpriteParameter(id) == NULL)
		SpriteParameterFactory::loadedSpriteParameters.insert(std::pair<std::string, SpriteParameter*>(id, loadedSpriteParameter));
}

SpriteParameter* SpriteParameterFactory::getLoadedSpriteParameter( std::string id )
{
	std::map<std::string, SpriteParameter*>::iterator it;
	it = SpriteParameterFactory::loadedSpriteParameters.find(id);

	if(it != SpriteParameterFactory::loadedSpriteParameters.end())
	{
		return it->second;
	}

	return NULL;	
}

void SpriteParameterFactory::uninit()
{
	for( std::map<std::string, SpriteParameter*>::iterator it = SpriteParameterFactory::loadedSpriteParameters.begin() ; it != SpriteParameterFactory::loadedSpriteParameters.end(); it++ )
	{
		if((*it).second != NULL)
		{
			delete (*it).second;
			(*it).second = NULL;
		}
	}	
}







