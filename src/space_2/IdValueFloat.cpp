#include "IdValueFloat.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
IdValueFloat::IdValueFloat( std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd )
{
	this->compute(p_idValue, p_valueDelimeterBegin, p_valueDelimeterEnd);
}

IdValueFloat::~IdValueFloat(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void IdValueFloat::compute( std::string p_idValue, std::string p_valueDelimeterBegin , std::string p_valueDelimeterEnd )
{
	if(p_idValue != "NULL")
	{
		int startDelimeter = p_idValue.find(p_valueDelimeterBegin);
		int endDemimeter = p_idValue.find(p_valueDelimeterEnd);
		this->setId(Tools::getLongFromString(p_idValue.substr(0, startDelimeter)));
		this->setValue(Tools::getFloatFromString(p_idValue.substr(startDelimeter+1, endDemimeter-startDelimeter-1)));
	}
}
