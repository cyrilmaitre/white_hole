#pragma once
#include "Map.h"
#include "Object.h"

// Define
#define CAMERA_PLANE						MAPOBJECT_PLANE_1
#define CAMERA_SCREENSIZE_MULTIPLIER		2.0

class Camera
{
public:
	// Constructor - Destructor
	Camera(void);
	~Camera(void);

	// Getters - Setters
	double getCameraX();
	double getCameraY();
	void setCameraX(double p_x);
	void setCameraY(double p_y);
	void setCameraPosition(double p_x, double p_y);

	sf::Vector2f getPositionInPlane(int p_plane);
	float getPlaneWidth(int p_plane);
	float getCameraPlaneWidth();
	float getPlaneHeight(int p_plane);
	float getCameraPlaneHeight();

	float getZoom();
	float getZoom(int p_plane);
	void setZoom(float p_zoom);

	// Methods
	void draw();
	void incZoom();
	void decZoom();

	void notifyZoomChanged();
	void notifyPositionChanged();

	static Camera* getInstance();
	static void destroyInstance();
	static sf::Vector2f* centerPosition(sf::Vector2f* p_position, int p_plane);
	static sf::Vector2f getObjectPositionInScreen(MapObject* p_object);

	// Attributs
	static sf::Vector2f frameCameraOffset;


private:
	// Attributs
	double mCameraX;		// Coordonnee x camera plane 1
	double mCameraY;		// Coordonnee y camera plane 1
	float mZoom;

	static Camera *mInstance;
};
