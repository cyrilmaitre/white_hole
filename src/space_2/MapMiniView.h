#pragma once
#include "Block.h"
#include "MapObject.h"

class Map;

class MapMiniView : public Block
{
public:
	// Constructor - Destructor
	MapMiniView(void);
	~MapMiniView(void);

	// Getters - Setters
	int getWidth();
	int getHeight();

	int getSectorMiniWidth();
	int getSectorMiniHeight();

	Map* getMap();
	void setMap(Map* p_map);

	float getZoom();
	void setZoom(float p_zoom);
	bool isZoomChanged();

	bool isMapObjectTypeDraw(MapObject::MapObjectType p_type);
	bool isMapObjectTypeMiniDraw(MapObject::MapObjectType p_type);
	bool isEntityTypeDraw(MapObject::MapObjectType p_type);
	bool isEntityTypeMiniDraw(MapObject::MapObjectType p_type);
	std::string getObjectMiniId(MapObject::MapObjectType p_type);

	// Methods
	void notifyPositionChanged();
	void notifySizeChanged();
	void notifyZoomChanged();
	void update();
	void updatePosition();
	void updateTexture();
	void createTexture();
	void createTextureObject();
	void createTextureBackground();
	void createTextureForeground();
	void createTextureBackgroundColor();
	void createTextureFirstPlane();
	void draw();


private:
	// Attribut
	Map* mMap;
	float mZoom;
	bool mZoomChanged;
	mks::Clock mClockRefreshFirstPlane;

	sf::RectangleShape mCrossHorizontal;
	sf::RectangleShape mCrossVertical;

	sf::Sprite mSpriteBackground;
	sf::Sprite mSpriteForeground;
	sf::Sprite mSpriteFirstPlane;
	sf::RenderTexture *mTextureBackground;
	sf::RenderTexture *mTextureForeground;
	sf::RenderTexture *mTextureFirstPlane;
	int mTextureOffsetX;
	int mTextureOffsetY;
	int mTextureColumn;
	int mTextureLine;

	Sector* mPreviousSector;
	int mPreviousSectorXBegin;
	int mPreviousSectorXEnd;
	int mPreviousSectorYBegin;
	int mPreviousSectorYEnd;

	std::map<MapObject::MapObjectType, float> mMapObjectTypeZoom;
	std::map<MapObject::MapObjectType, float> mMapObjectTypeMiniZoom;

	std::map<MapObject::MapObjectType, float> mEntityTypeZoom;
	std::map<MapObject::MapObjectType, float> mEntityTypeMiniZoom;
};

