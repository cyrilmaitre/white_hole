#include "Particle.h"
#include "Camera.h"
#include "ParticleManager.h"


//*************************************************************
// Define
//*************************************************************
#define PARTICLE_COLOR_PLAN_2				sf::Color(255, 255, 255)
#define PARTICLE_COLOR_PLAN_7				sf::Color(215, 215, 215)
#define PARTICLE_COLOR_PLAN_12				sf::Color(175, 175, 175)
#define PARTICLE_COLOR_PLAN_16				sf::Color(135, 135, 135)
#define PARTICLE_VELOCITYMAX_MARGIN_MIN		0
#define PARTICLE_VELOCITYMAX_MARGIN_MAX		50
#define PARTICLE_SIZE						1


//*************************************************************
// Contructor - Destructor
//*************************************************************
Particle::Particle( double p_x, double p_y, float p_velocityMax, float p_quickening, int p_plane )
{
	// Set with param
	this->setPlane(p_plane);
	this->setX(p_x);
	this->setY(p_y);
	this->setVelocityMax(p_velocityMax + p_velocityMax * Tools::randomPercentage(PARTICLE_VELOCITYMAX_MARGIN_MIN, PARTICLE_VELOCITYMAX_MARGIN_MAX));
	this->setVelocityAt(MovableCardinality::East, this->getVelocityMax());
	this->setQuickening(p_quickening);

	particle.setSize(sf::Vector2f(PARTICLE_SIZE, PARTICLE_SIZE));
	particle.setFillColor(this->getColor());
}

Particle::~Particle(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
double Particle::getX()
{
	return this->mX;
}

void Particle::setX( double p_x )
{
	float planeWidth = Resource::resource->getViewUi()->getSize().x;

	// Check param
	if(p_x < 0)
		p_x = (planeWidth - 1) + p_x;
	else if(p_x > (planeWidth - 1))
		p_x = p_x - (planeWidth - 1);

	// Set
	this->mX = p_x;
}

double Particle::getY()
{
	return this->mY;
}

void Particle::setY( double p_y )
{
	float planeHeight = Resource::resource->getViewUi()->getSize().y;

	// Check param
	if(p_y < 0)
		p_y = (planeHeight - 1) + p_y;
	else if(p_y > (planeHeight - 1))
		p_y = p_y - (planeHeight - 1);

	// Set
	this->mY = p_y;
}

int Particle::getPlane()
{
	return this->mPlane;
}

void Particle::setPlane(int p_plane)
{
	this->mPlane = p_plane;
}

sf::Color Particle::getColor()
{
	switch(this->getPlane())
	{
	case MAPOBJECT_PLANE_2:
		return PARTICLE_COLOR_PLAN_2;
		break;

	case MAPOBJECT_PLANE_7:
		return PARTICLE_COLOR_PLAN_7;
		break;

	case MAPOBJECT_PLANE_12:
		return PARTICLE_COLOR_PLAN_12;
		break;

	case MAPOBJECT_PLANE_16:
		return PARTICLE_COLOR_PLAN_16;
		break;

	default:
		return PARTICLE_COLOR_PLAN_2;
	}
}


//*************************************************************
// Methode
//*************************************************************
void Particle::draw()
{
	particle.setPosition(this->getX(), this->getY());
	ParticleManager::getParticlesTexture()->draw(particle);
}

void Particle::update()
{
	float tmpX = this->getX() - MapObject::convertSize(Camera::frameCameraOffset.x, MAPOBJECT_PLANE_1, this->getPlane());
	float tmpY = this->getY() - MapObject::convertSize(Camera::frameCameraOffset.y, MAPOBJECT_PLANE_1, this->getPlane());
	float varX = 0;

	varX += MapObject::convertSize(this->getVelocityAt(MovableCardinality::East) * ((float)this->mVelocityClock.getElapsedTimeAsMilliseconds() / 1000.f), MAPOBJECT_PLANE_1, this->getPlane());
	this->mVelocityClock.restart();

	this->setX(tmpX + varX);
	this->setY(tmpY);
}	


