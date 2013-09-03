#pragma once
#include "SpriteParameter.h"
#include "SpriteParameterDefine.h"

// Define
#define SP_ID_UIGAMEWINDOW_BUTTON		IMG_WINDOW_ACTIONBARBUTTON
#define SP_ID_UIGAME_ICON10X10			IMG_ICON10X10
#define SP_ID_UIGAME_ICON16X16			IMG_ICON16X16
#define SP_ID_UIGAME_ICON32X32			IMG_ICON32X32
#define SP_ID_UIGAME_ICON48X48			IMG_ICON48X48
#define SP_ID_UIGAME_ICON64X64			IMG_ICON64X64
#define SP_ID_SPACE_BACKGROUND			IMG_SPACE_BACKGROUND
#define SP_ID_SCROLLBAR					IMG_SCROLLBAR
#define SP_ID_RACE						IMG_RACE
#define SP_ID_AVATAR					IMG_AVATAR
#define SP_ID_JOB						IMG_JOB
#define SP_ID_SKILL						IMG_SKILL
#define SP_ID_ITEMS						IMG_ITEMS
#define SP_ID_IMPACT_LASER				IMG_IMPACT_LASER
#define SP_ID_IMPACT_EXPLOSION			IMG_IMPACT_EXPLOSION
#define SP_ID_LOADING_SQUARE_CIRCLE		IMG_LOADING_SQUARE_CIRCLE

class SpriteParameterFactory
{
public:
	// Methods
	static SpriteParameter* getSpriteParameterWindowButton(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterIcon10X10(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterIcon16X16(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterIcon32X32(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterIcon48X48(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterIcon64X64(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterSpaceBackground(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterScrollbar(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterRace(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterAvatar(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterJob(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterSkill(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterItems(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterImpactLaser(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterImpactExplosion(bool useLoaded = true);
	static SpriteParameter* getSpriteParameterLoadingSquareCircle(bool useLoaded = true);
	static SpriteParameter* getSpriteParameter(std::string id, int spriteColumn, int spriteLine, bool useLoaded = true);
	static void uninit();


protected:
	// Constructor - Destructor
	SpriteParameterFactory(void);
	~SpriteParameterFactory(void);


private:
	// Methods
	static void addLoadedSpriteParameters(std::string id, SpriteParameter* loadedSpriteParameter);
	static SpriteParameter* getLoadedSpriteParameter(std::string id);
	static std::map<std::string, SpriteParameter*> loadedSpriteParameters;
};

