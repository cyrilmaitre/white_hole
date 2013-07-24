#include "ParticleManager.h"
#include "Camera.h"
#include "Game.h"


//*************************************************************
// Define
//*************************************************************
#define PARTICLE_VELOCITY			30				// Particle Velocity
#define PARTICLE_DENSITY_BY_PLAN	0.2				// Particle number by plan by 100*100 px


//*************************************************************
// Init statics
//*************************************************************
Particle * ParticleManager::mParticles[];
int ParticleManager::mNextIndex;
sf::RenderTexture * ParticleManager::mParticlesTexture = NULL;


//*************************************************************
// Constructreur - Destructeur
//*************************************************************
ParticleManager::ParticleManager(void)
{
	ParticleManager::resizeParticlesTexture();
}

ParticleManager::~ParticleManager(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
sf::RenderTexture* ParticleManager::getParticlesTexture()
{
	return ParticleManager::mParticlesTexture;
}

int ParticleManager::getParticleCount()
{
	return ParticleManager::mNextIndex;
}

int ParticleManager::getParticleCountMax()
{
	return PARTICLE_TAB_NUMBER;
}

//*************************************************************
// Méthode
//*************************************************************
void ParticleManager::init()
{
	// Init particles
	for(int i = 0; i < PARTICLE_TAB_NUMBER; i++)
	{
		ParticleManager::mParticles[i] = NULL;
	}

	// Init next index
	ParticleManager::mNextIndex = 0;
}

void ParticleManager::uninit()
{
	ParticleManager::destroyeParticle();
}

bool ParticleManager::addParticle( Particle *myParticle )
{
	// Check nextIndex
	if(ParticleManager::mNextIndex >= PARTICLE_TAB_NUMBER)
	{
		delete myParticle;
		return false;
	}

	// Save particle at index
	ParticleManager::mParticles[ParticleManager::mNextIndex] = myParticle;
	ParticleManager::mNextIndex++;
	return true;
}

void ParticleManager::destroyeParticle()
{
	// Destroye all particle
	for(int i = 0; i < PARTICLE_TAB_NUMBER; i++)
	{
		if(ParticleManager::mParticles[i] != NULL)
		{
			delete ParticleManager::mParticles[i];
			ParticleManager::mParticles[i] = NULL;
		}
	}

	// Reset nextIndex
	ParticleManager::mNextIndex = 0;
}

void ParticleManager::generateParticle()
{
	// Destroye particle
	ParticleManager::destroyeParticle();

	// Init
	int particlePlanNumber = (int)(((Resource::resource->getViewUi()->getSize().x * Resource::resource->getViewUi()->getSize().y) / 10000)  * PARTICLE_DENSITY_BY_PLAN);
	int currentParticleX;
	int currentParticleY;

	// Particle Generation
	for(int i = 0; i < particlePlanNumber; i++)
	{
		// Plan 2
		currentParticleX = rand() % (int)Resource::resource->getViewUi()->getSize().x;
		currentParticleY = rand() % (int)Resource::resource->getViewUi()->getSize().y;
		ParticleManager::addParticle(new Particle((float)currentParticleX, (float)currentParticleY, PARTICLE_VELOCITY, 0, MAPOBJECT_PLANE_2));

		// Plan 
		currentParticleX = rand() % (int)Resource::resource->getViewUi()->getSize().x;
		currentParticleY = rand() % (int)Resource::resource->getViewUi()->getSize().y;
		ParticleManager::addParticle(new Particle((float)currentParticleX, (float)currentParticleY, PARTICLE_VELOCITY, 0, MAPOBJECT_PLANE_7));

		// Plan 12
		currentParticleX = rand() % (int)Resource::resource->getViewUi()->getSize().x;
		currentParticleY = rand() % (int)Resource::resource->getViewUi()->getSize().y;
		ParticleManager::addParticle(new Particle((float)currentParticleX, (float)currentParticleY, PARTICLE_VELOCITY, 0, MAPOBJECT_PLANE_12));

		// Plan 16
		currentParticleX = rand() % (int)Resource::resource->getViewUi()->getSize().x;
		currentParticleY = rand() % (int)Resource::resource->getViewUi()->getSize().y;
		ParticleManager::addParticle(new Particle((float)currentParticleX, (float)currentParticleY, PARTICLE_VELOCITY, 0, MAPOBJECT_PLANE_16));
	}
}

void ParticleManager::resizeParticlesTexture()
{
	if(ParticleManager::mParticlesTexture == NULL)
	{
		ParticleManager::mParticlesTexture = new sf::RenderTexture();
	}

	ParticleManager::mParticlesTexture->create(Resource::resource->getViewUi()->getSize().x, Resource::resource->getViewUi()->getSize().y);
}

void ParticleManager::handleScreenAppResized()
{
	ParticleManager::resizeParticlesTexture();
	ParticleManager::generateParticle();
}

void ParticleManager::update()
{	
	// Update
	for(int i = 0; i < PARTICLE_TAB_NUMBER; i++)
	{
		if(ParticleManager::mParticles[i] != NULL)
			ParticleManager::mParticles[i]->update();
	}
}

void ParticleManager::draw()
{
	// Clear particlesTextures
	ParticleManager::mParticlesTexture->clear(sf::Color(0,0,0,0));

	// Draw into particlesTexture
	for(int i = 0; i < PARTICLE_TAB_NUMBER; i++)
	{
		if(ParticleManager::mParticles[i] != NULL)
			ParticleManager::mParticles[i]->draw();
	}

	// Draw particlesTexture
	ParticleManager::mParticlesTexture->display();
	sf::Sprite sprite(ParticleManager::mParticlesTexture->getTexture());
	Resource::resource->getApp()->draw(sprite);
}


