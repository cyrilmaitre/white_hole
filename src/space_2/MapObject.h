#pragma once
#include "Resource.h"
#include "EventManager.h"
#include "Selectable.h"
#include "SpriteParameter.h"
#include "IdGenerator.h"
#include "TextBox.h"
#include "Clock.h"
#include "Rotable.h"


// Define
#define MAPOBJECT_PLANE_DEFAULT				MAPOBJECT_PLANE_1
#define MAPOBJECT_PLANE_NUMBER				21
//-----
#define MAPOBJECT_PLANE_1					0		// Ship, asteroid...etc
#define MAPOBJECT_PLANE_1_RATIO				1.f	
//-----
#define MAPOBJECT_PLANE_2					1		// Particles 1
#define MAPOBJECT_PLANE_2_RATIO				0.95
//-----
#define MAPOBJECT_PLANE_3					2		// Free
#define MAPOBJECT_PLANE_3_RATIO				0.9
//-----
#define MAPOBJECT_PLANE_4					3		// Free
#define MAPOBJECT_PLANE_4_RATIO				0.85
//-----
#define MAPOBJECT_PLANE_5					4		// Free
#define MAPOBJECT_PLANE_5_RATIO				0.8
//-----
#define MAPOBJECT_PLANE_6					5		// Free
#define MAPOBJECT_PLANE_6_RATIO				0.75
//-----
#define MAPOBJECT_PLANE_7					6		// Particles 2
#define MAPOBJECT_PLANE_7_RATIO				0.7
//-----
#define MAPOBJECT_PLANE_8					7		// Free
#define MAPOBJECT_PLANE_8_RATIO				0.65
//-----
#define MAPOBJECT_PLANE_9					8		// Free
#define MAPOBJECT_PLANE_9_RATIO				0.6
//-----
#define MAPOBJECT_PLANE_10					9		// Free
#define MAPOBJECT_PLANE_10_RATIO			0.55
//-----
#define MAPOBJECT_PLANE_11					10		// Free
#define MAPOBJECT_PLANE_11_RATIO			0.5
//-----
#define MAPOBJECT_PLANE_12					11		// Particles 3
#define MAPOBJECT_PLANE_12_RATIO			0.45
//-----
#define MAPOBJECT_PLANE_13					12		// Free
#define MAPOBJECT_PLANE_13_RATIO			0.4
//-----
#define MAPOBJECT_PLANE_14					13		// Cloud Wreck
#define MAPOBJECT_PLANE_14_RATIO			0.35
//-----
#define MAPOBJECT_PLANE_15					14		// Free
#define MAPOBJECT_PLANE_15_RATIO			0.3
//-----
#define MAPOBJECT_PLANE_16					15		// Particles 4
#define MAPOBJECT_PLANE_16_RATIO			0.25
//-----
#define MAPOBJECT_PLANE_17					16		// Cloud Gaz
#define MAPOBJECT_PLANE_17_RATIO			0.1
//-----
#define MAPOBJECT_PLANE_18					17		// Planet
#define MAPOBJECT_PLANE_18_RATIO			0.07
//-----
#define MAPOBJECT_PLANE_19					18		// Planet
#define MAPOBJECT_PLANE_19_RATIO			0.05
//-----
#define MAPOBJECT_PLANE_20					19		// Planet
#define MAPOBJECT_PLANE_20_RATIO			0.03
//-----
#define MAPOBJECT_PLANE_21					20		// Background
#define MAPOBJECT_PLANE_21_RATIO			0.02
//-----
#define MAPOBJECT_UNLOADSPRITE_DELAY		10	// Sec

class Sector;

class MapObject: public Selectable, public Rotable
{
public:
	// Enum
	enum MapObjectType 
	{
		TypeMapObject = 0,
		TypeShip,
		TypeCharacterShip,
		TypeNpcShip,
		TypePlanet,
		TypeCloudGaz,
		TypeCloudWreck,
		TypeWreck,
		TypeWreckMini,
		TypeStar,
		TypeStation
	};

	enum MapObjectOpacity
	{
		Opacity0 = 100,
		Opacity1 = 90,
		Opacity2 = 80,
		Opacity3 = 70,
		Opacity4 = 60,
		Opacity5 = 50,
		Opacity6 = 40,
		Opacity7 = 30,
		Opacity8 = 20,
		Opacity9 = 10,
		Opacity10 = 0
	};

	// Constructor - Destructor
	MapObject(int p_plane = MAPOBJECT_PLANE_DEFAULT);
	virtual ~MapObject(void);

	// Getters - Setters
	long getId();
	void setId(long p_id);

	double getX(int plane);
	double getSectorX();
	double getCenterX(int plane);
	float getScreenX();
	double getY(int plane);
	double getSectorY();
	double getCenterY(int plane);
	float getScreenY();

	void setWidth(int p_witdh);
	void setHeight(int p_height);
	void setSize(int p_witdh, int p_height);

	sf::FloatRect getHitBox();
	int getWidth(int p_plane);
	int getHeight(int p_plane);
	int getRadius();

	sf::Vector2f getScreenPosition();
	sf::Vector2f getPosition(int plane);
	sf::Vector2f getCenterPosition(int plane);

	int getPlane();
	void setPlane(int p_plane);

	MapObjectType getObjectType();
	std::string getObjectTypeName();
	void setObjectType(MapObjectType p_type);

	MapObjectOpacity getObjectOpacity();
	void setObjectOpacity(MapObjectOpacity p_opacity);

	bool hasSector();
	Sector* getSector();
	void setSector(Sector* p_sector);

	float getScale();
	void setScale(float p_scale);

	bool isSpriteLoaded();
	sf::Sprite* getObjectSprite();
	bool hasObjectSprite();
	int getObjectSpriteWidth();
	int getObjectSpriteHeight();
	int getObjectSpriteRadius();
	SpriteParameter* getObjectSpriteParameter();
	bool hasObjectSpriteParameter();

	// Methode
	virtual void draw();
	virtual void update();
	virtual void update(sf::Event p_event);
	virtual void updateSprite();
	void updateScreenPosition();
	void updateVisible();
	virtual void updateHitBox();
	void notifyVisibleChanged();
	void notifyScreenPositionChanged();
	void notifySizeChanged();
	virtual void notifyRotationChanged();
	virtual void notifyScaleChanged();

	void activateSelectable();
	void desactivateSelectable();
	void activateClickable();
	void desactivateClickable();
	void activateFocusable();
	void desactivateFocusable();
	void activateOverable();
	void desactivateOverable();

	virtual void loadSprite();
	virtual void unloadSprite();
	void setObjectSprite(std::string p_sprite);

	bool intersect(MapObject* p_object);			// On s Same Plane
	int cover(MapObject* p_object);					// On screen
	float coverPercent(MapObject* p_object);		// On screen	

	// Static methods
	static void init();
	static sf::Vector2f convertPosition(sf::Vector2f position, int sourcePlane, int destinationPlane);
	static sf::Vector2i convertPosition(sf::Vector2i position, int sourcePlane, int destinationPlane);
	static float convertSize(float size, int sourcePlane, int destinationPlane);
	static int convertSize(int size, int sourcePlane, int destinationPlane);
	static float getPlaneRatio(int plane);
	static int getPlaneForeground();
	static int getPlaneBackground();


protected:
	// Attributs
	long mId;
	int mPlane;
	float mScale;
	sf::FloatRect mHitBox;							// On screen
	MapObjectType mObjectType;
	MapObjectOpacity mObjectOpacity;

	Sector* mSector;
	sf::Vector2f mScreenPosition;

	sf::Sprite *mObjectSprite;
	SpriteParameter *mObjectSpriteParameter;
	
	mks::Clock mObjectClock;

	// Static
	static float mPlaneRatio[MAPOBJECT_PLANE_NUMBER];
	static IdGenerator mIdGenerator;


private:
	// Methods
	void updateMouseOver();
};