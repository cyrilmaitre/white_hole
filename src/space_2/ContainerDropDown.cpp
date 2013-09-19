#include "ContainerDropDown.h"
#include "CharacterBank.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
ContainerDropDown::ContainerDropDown( Containerable* p_container )
{
	this->setContainer(p_container);
}

ContainerDropDown::~ContainerDropDown(void)
{
}


//*************************************************************
// Getters - Setters
//*************************************************************
Containerable* ContainerDropDown::getContainer()
{
	return this->mContainer;
}

void ContainerDropDown::setContainer( Containerable* p_container )
{
	if(this->mContainer != p_container)
	{
		this->mContainer = p_container;
		this->notifyContainerChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void ContainerDropDown::notifyContainerChanged()
{
	if(this->mContainer != NULL)
	{
		if(this->mContainer->getType() == ContainerStack::ContainerStackType::TypeCharacterShip)
			this->setText(Resource::resource->getBundle()->getString("shipCargo"));
		else if(this->mContainer->getType() == ContainerStack::ContainerStackType::TypeCharacterBank)
			this->setText(Resource::resource->getBundle()->getString("bankCargo") + Tools::buildStringWithInt(((CharacterBank*)this->mContainer)->getNumber()));
		else
			this->setText("ERROR");
	}
}
