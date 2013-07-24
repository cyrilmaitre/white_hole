#pragma once
#include "Particle.h"

// Define
#define PARTICLE_TAB_NUMBER			500	// Max particle number

class ParticleManager
{
public:
	// Getters - Setters
	static sf::RenderTexture* getParticlesTexture();
	static int getParticleCount();
	static int getParticleCountMax();

	// Methods
  	static void init();
	static void uninit();

	static bool addParticle(Particle *myParticle);
	static void generateParticle();
	static void destroyeParticle();
	static void resizeParticlesTexture();
	static void handleScreenAppResized();

	static void update();
	static void draw();


protected:
	// Constructor - Destructor
	ParticleManager(void);
	~ParticleManager(void);


private:
	// Attibuts
	static Particle *mParticles[PARTICLE_TAB_NUMBER];
	static int mNextIndex;
	static sf::RenderTexture *mParticlesTexture;
};

