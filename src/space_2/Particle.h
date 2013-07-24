#pragma once
#include "Movable.h"
#include "MapObject.h"


class Particle : public Movable
{
public:
	// Constructor - Destructor
	Particle(double p_x, double p_y, float p_velocityMax, float p_quickening, int p_plane);
	~Particle(void);

	// Getters - Setters
	double getX();
	void setX(double p_x);

	double getY();
	void setY(double p_y);

	int getPlane();
	void setPlane(int p_plane);

	sf::Color getColor();

	// Methods
	void update();
	void draw();


private:
	double mX;
	double mY;
	int mPlane;

	sf::RectangleShape particle;
};

