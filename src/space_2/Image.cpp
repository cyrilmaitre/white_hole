#include "Image.h"

//*************************************************************
// Constructor - Destructor
//*************************************************************
Image::Image( void )
{
	this->setUpdateMouseOver(false);
	this->setUpdateFocus(false);
	this->setUpdateClicked(false);
	this->setUpdateSelected(false);
}

Image::~Image(void)
{
}
