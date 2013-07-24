#pragma once
#include "Resource.h"
#include "Object.h"
#include "Selectable.h"
#include "MapObject.h"
#include "Entity.h"

class ToolsImage
{
public:
	// Methods
	static void resizeSprite(sf::Sprite *p_sprite, int newWidth, int newHeight);
	static void resizeRectangleShape(sf::RectangleShape *p_shape, int newWidth, int newHeight);
	static void setSpriteOriginCenter(sf::Sprite* p_sprite);

	static sf::Color hexaToColor(const std::string p_string);
	static sf::Color getDarkerColor(sf::Color p_color, int indice);
	static sf::Color shadeColor(sf::Color p_color, int p_shade);
	static sf::ConvexShape* getReloadPolygon(float reloadPercent, Object *object);

	// Ui
	static void drawReloadPolygon(float reloadPercent, Object *object, sf::Color fillColor);
	static void drawBorder(int p_x, int p_y, int p_width, int p_height, sf::Color p_color, int p_size, sf::RenderTexture* p_target = NULL);
	static void drawBorder(Object* p_object, sf::Color p_color, int p_size);
	static void drawBorder(MapObject* p_object, sf::Color p_color, int p_size);
	static void drawBorder(Entity* p_object, sf::Color p_color, int p_size);
	static void drawBorderCircle(Object* p_object, sf::Color p_color, int p_size);
	static void drawBorderCircle(MapObject* p_object, sf::Color p_color, int p_size);
	static void drawBorderCircle(Entity* p_object, sf::Color p_borderColor, int p_borderSize, int p_circleSize = -1);


private:
	// Constructor - Destructor
	ToolsImage(void);
	~ToolsImage(void);

	// Methods
	static void drawBorderAt(double p_x, double p_y, int p_width, int p_height, sf::Color p_color, int p_size, sf::RenderTexture* p_target = NULL);
	static void drawBorderCircleAt(double p_x, double p_y, int p_radius, sf::Color p_color, int p_size);
};

