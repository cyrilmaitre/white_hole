#include "IdValueDouble.h"


//*************************************************************
// Constructor - Destructor
//*************************************************************
IdValueDouble::IdValueDouble( std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd )
{
	this->compute(p_idValue, p_valueDelimeterBegin, p_valueDelimeterEnd);
}

IdValueDouble::~IdValueDouble(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void IdValueDouble::compute( std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd )
{
	if(p_idValue != "NULL")
	{
		int startDelimeter = p_idValue.find(p_valueDelimeterBegin);
		int endDemimeter = p_idValue.find(p_valueDelimeterEnd);
		this->setId(Tools::getLongFromString(p_idValue.substr(0, startDelimeter)));
		this->setValue(Tools::getDoubleFromString(p_idValue.substr(startDelimeter+1, endDemimeter-startDelimeter-1)));
	}
}
