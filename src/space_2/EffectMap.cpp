#include "EffectMap.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
EffectMap::EffectMap( int p_plane ) : MapObject(p_plane)
{
	this->desactivateOverable();
}

EffectMap::~EffectMap(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void EffectMap::update()
{
	MapObject::update();
}

void EffectMap::draw()
{
	MapObject::draw();
}
