#include "ToolsImage.h"
#include "Camera.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ToolsImage::ToolsImage(void)
{
}

ToolsImage::~ToolsImage(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void ToolsImage::resizeSprite( sf::Sprite *p_sprite, int newWidth, int newHeight )
{
	if(p_sprite != NULL)
	{
		float widthFactor = 1;
		float heightFactor = 1;
		if(newWidth > 0)
			widthFactor = (float)newWidth / (float)p_sprite->getLocalBounds().width;
		if(newHeight > 0)
			heightFactor = (float)newHeight / (float)p_sprite->getLocalBounds().height;
		p_sprite->setScale(widthFactor, heightFactor);
	}
}

void ToolsImage::resizeRectangleShape( sf::RectangleShape *p_shape, int newWidth, int newHeight )
{
	if(p_shape != NULL)
	{
		float widthFactor = 1;
		float heightFactor = 1;
		if(newWidth > 0)
			widthFactor = (float)newWidth / (float)p_shape->getLocalBounds().width;
		if(newHeight > 0)
			heightFactor = (float)newHeight / (float)p_shape->getLocalBounds().height;
		p_shape->setScale(widthFactor, heightFactor);
	}
}

sf::Color ToolsImage::hexaToColor( const std::string p_string )
{
	sf::Color color = sf::Color::Black;
	if (p_string.size() == 7)
	{
		color.r = strtoul(p_string.substr(1, 2).c_str(), NULL, 16);
		color.g = strtoul(p_string.substr(3, 2).c_str(), NULL, 16);
		color.b = strtoul(p_string.substr(5, 2).c_str(), NULL, 16);
	}
	return color;

}

sf::ConvexShape* ToolsImage::getReloadPolygon( float reloadPercent, Object *object )
{
	sf::ConvexShape *polygon = new sf::ConvexShape();

	// Set PointCount
	if(reloadPercent < 0.125)			polygon->setPointCount(3);
	else if(reloadPercent < 0.25)		polygon->setPointCount(4);
	else if(reloadPercent < 0.375)		polygon->setPointCount(5);
	else if(reloadPercent < 0.5)		polygon->setPointCount(6);
	else if(reloadPercent < 0.625)		polygon->setPointCount(7);
	else if(reloadPercent < 0.75)		polygon->setPointCount(8);
	else if(reloadPercent < 0.875)		polygon->setPointCount(9);
	else								polygon->setPointCount(10);

	// Set Point
	polygon->setPoint(0, sf::Vector2f(object->getCenterX(), object->getCenterY()));
	polygon->setPoint(1, sf::Vector2f(object->getCenterX(), object->getY()));
	if(reloadPercent < 0.25)
	{
		if(reloadPercent < 0.125)
		{
			polygon->setPoint(2, sf::Vector2f(object->getX() + (object->getWidth() / 2) * (1 - (reloadPercent / 0.125)), object->getY()));
		}
		else
		{
			polygon->setPoint(2, sf::Vector2f(object->getX(), object->getY()));
			polygon->setPoint(3, sf::Vector2f(object->getX(), object->getY() + (object->getHeight() / 2) * ((reloadPercent - 0.125) / 0.125)));
		}
	}
	else
	{
		polygon->setPoint(2, sf::Vector2f(object->getX(), object->getY()));
		polygon->setPoint(3, sf::Vector2f(object->getX(), object->getY() + (object->getHeight() / 2)));
		if(reloadPercent < 0.5)
		{
			if(reloadPercent < 0.375)
			{
				polygon->setPoint(4, sf::Vector2f(object->getX(), object->getY() + (object->getHeight() / 2) * (1 + ((reloadPercent - 0.25) / 0.125))));
			}
			else
			{
				polygon->setPoint(4, sf::Vector2f(object->getX(), object->getY() + object->getHeight()));
				polygon->setPoint(5, sf::Vector2f(object->getX() + (object->getWidth() / 2) * ((reloadPercent - 0.375) / 0.125), object->getY() + object->getHeight()));
			}
		}
		else
		{
			polygon->setPoint(4, sf::Vector2f(object->getX(), object->getY() + object->getHeight()));
			polygon->setPoint(5, sf::Vector2f(object->getX() + (object->getWidth() / 2), object->getY() + object->getHeight()));
			if(reloadPercent < 0.75)
			{
				if(reloadPercent < 0.625)
				{
					polygon->setPoint(6, sf::Vector2f(object->getX() + (object->getWidth() / 2) * (1 + (reloadPercent - 0.5) / 0.125), object->getY() + object->getHeight()));
				}
				else
				{
					polygon->setPoint(6, sf::Vector2f(object->getX() + object->getWidth(), object->getY() + object->getHeight()));
					polygon->setPoint(7, sf::Vector2f(object->getX() + object->getWidth(), object->getY() + object->getHeight() - ((object->getHeight() / 2) * ((reloadPercent - 0.625) / 0.125))));
				}
			}
			else
			{
				polygon->setPoint(6, sf::Vector2f(object->getX() + object->getWidth(), object->getY() + object->getHeight()));
				polygon->setPoint(7, sf::Vector2f(object->getX() + object->getWidth(), object->getY() + (object->getHeight() / 2)));
				if(reloadPercent < 0.875)
				{
					polygon->setPoint(8, sf::Vector2f(object->getX() + object->getWidth(), object->getY() + (object->getHeight() / 2) * (1 - ((reloadPercent - 0.75) / 0.125))));
				}
				else
				{
					polygon->setPoint(8, sf::Vector2f(object->getX() + object->getWidth(), object->getY()));
					polygon->setPoint(9, sf::Vector2f(object->getX() + (object->getWidth() / 2) * (2 - ((reloadPercent - 0.875) / 0.125)), object->getY()));
				}
			}
		}
	}

	// Return
	return polygon;
}

void ToolsImage::drawReloadPolygon( float reloadPercent, Object *object, sf::Color fillColor )
{
	sf::ConvexShape *polygon = ToolsImage::getReloadPolygon(reloadPercent, object);
	polygon->setFillColor(fillColor);	
	Resource::resource->getApp()->draw(*polygon);
	delete polygon;
}

void ToolsImage::drawBorder( Object* p_object, sf::Color p_color, int p_size )
{
	ToolsImage::drawBorderAt(p_object->getX(), p_object->getY(), p_object->getWidth(), p_object->getHeight(), p_color, p_size);
}

void ToolsImage::drawBorder( MapObject* p_object, sf::Color p_color, int p_size )
{
	sf::Vector2f objectPositionScreen = p_object->getScreenPosition();
	ToolsImage::drawBorderAt(	objectPositionScreen.x - p_object->getWidthHalf(), objectPositionScreen.y - p_object->getHeightHalf(), 
								p_object->Object::getWidth(), p_object->Object::getHeight(), p_color, p_size);
}

void ToolsImage::drawBorder( int p_x, int p_y, int p_width, int p_height, sf::Color p_color, int p_size, sf::RenderTexture* p_target )
{
	ToolsImage::drawBorderAt(p_x, p_y, p_width, p_height, p_color, p_size, p_target);
}

void ToolsImage::drawBorder( Entity* p_object, sf::Color p_color, int p_size )
{
	sf::Vector2f objectPositionScreen = p_object->getScreenPosition();
	ToolsImage::drawBorderAt(	objectPositionScreen.x + p_object->getWidthHalf(), objectPositionScreen.y - p_object->getHeightHalf() + p_object->getRocking(), 
								p_object->Object::getWidth(), p_object->Object::getHeight(), p_color, p_size);
}

void ToolsImage::drawBorderCircle( Object* p_object, sf::Color p_color, int p_size )
{
	int radius = p_object->Object::getWidth() > p_object->Object::getHeight() ? p_object->Object::getWidth() : p_object->Object::getHeight();
	ToolsImage::drawBorderCircleAt(p_object->getX(), p_object->getY(), radius / 2, p_color, p_size);
}

void ToolsImage::drawBorderCircle( MapObject* p_object, sf::Color p_color, int p_size )
{
	int radius = p_object->Object::getWidth() > p_object->Object::getHeight() ? p_object->Object::getWidth() : p_object->Object::getHeight();
	sf::Vector2f objectPositionScreen = p_object->getScreenPosition();
	ToolsImage::drawBorderCircleAt(	objectPositionScreen.x, objectPositionScreen.y, radius / 2, p_color, p_size);
}

void ToolsImage::drawBorderCircle( Entity* p_object, sf::Color p_borderColor, int p_borderSize, int p_circleSize )
{
	int radius = 0;
	if(p_circleSize != -1)
		radius = p_circleSize;
	else
		radius = p_object->Object::getWidth() > p_object->Object::getHeight() ? p_object->Object::getWidth() : p_object->Object::getHeight();
	sf::Vector2f objectPositionScreen = p_object->getScreenPosition();
	ToolsImage::drawBorderCircleAt(	objectPositionScreen.x, objectPositionScreen.y + p_object->getRocking(), radius / 2, p_borderColor, p_borderSize);
}

void ToolsImage::drawBorderAt( double p_x, double p_y, int p_width, int p_height, sf::Color p_color, int p_size, sf::RenderTexture* p_target )
{
	if(p_size == 0)
		return;

	sf::RectangleShape border;

	// Top
	border.setPosition((float)(p_x - p_size), (float)(p_y - p_size));
	border.setSize(sf::Vector2f((float)(2*p_size + p_width), (float)p_size));
	border.setFillColor(p_color);
	if(p_target != NULL)
		p_target->draw(border);
	else
		Resource::resource->getApp()->draw(border);

	// Bottom
	border.setPosition((float)(p_x - p_size), (float)(p_y + p_height));
	border.setSize(sf::Vector2f((float)(2*p_size + p_width), (float)p_size));
	border.setFillColor(p_color);
	if(p_target != NULL)
		p_target->draw(border);
	else
		Resource::resource->getApp()->draw(border);

	// Left
	border.setPosition((float)(p_x - p_size), (float)(p_y));
	border.setSize(sf::Vector2f((float)p_size, (float)(p_height)));
	border.setFillColor(p_color);
	if(p_target != NULL)
		p_target->draw(border);
	else
		Resource::resource->getApp()->draw(border);

	// Right
	border.setPosition((float)(p_x + p_width), (float)(p_y));
	border.setSize(sf::Vector2f((float)p_size, (float)(p_height)));
	border.setFillColor(p_color);
	if(p_target != NULL)
		p_target->draw(border);
	else
		Resource::resource->getApp()->draw(border);
}

void ToolsImage::drawBorderCircleAt( double p_x, double p_y, int p_radius, sf::Color p_color, int p_size )
{
	sf::CircleShape circle;
	circle.setRadius(p_radius);
	circle.setOutlineColor(p_color);
	circle.setOutlineThickness(p_size);
	circle.setPosition(p_x, p_y);
	circle.setOrigin(p_radius, p_radius);
	circle.setFillColor(sf::Color(0, 0, 0, 0));
	Resource::resource->getApp()->draw(circle);
}

void ToolsImage::setSpriteOriginCenter( sf::Sprite* p_sprite )
{
	p_sprite->setOrigin(p_sprite->getLocalBounds().width / 2, p_sprite->getLocalBounds().height / 2);
}

sf::Color ToolsImage::getDarkerColor( sf::Color p_color, int indice )
{
	if(p_color.r < indice)
		p_color.r = 0;
	else
		p_color.r -= indice;
	
	if(p_color.g < indice)
		p_color.g = 0;
	else
		p_color.g -= indice;

	if(p_color.b < indice)
		p_color.b = 0;
	else
		p_color.b -= indice;

	return p_color;
}

sf::Color ToolsImage::shadeColor( sf::Color p_color, int p_shade )
{
	int newR = Tools::random(p_color.r - p_shade, p_color.r + p_shade);
	if(newR > 255) newR = 255;
	else if(newR < 0) newR = 0;
	p_color.r = newR;

	int newG = Tools::random(p_color.g - p_shade, p_color.g + p_shade);
	if(newG > 255) newG = 255;
	else if(newG < 0) newG = 0;
	p_color.g = newG;

	int newB = Tools::random(p_color.b - p_shade, p_color.b + p_shade);
	if(newB > 255) newB = 255;
	else if(newB < 0) newB = 0;
	p_color.b = newB;
	return p_color;
}

