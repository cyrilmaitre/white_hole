#pragma once
#include "IdValue.h"

class IdValueFloat : public IdValue<float>
{
public:
	// Constructor - Destructor
	IdValueFloat(std::string p_idValue, std::string p_valueDelimeterBegin = "(" , std::string p_valueDelimeterEnd = ")");
	~IdValueFloat(void);

	
protected:
	// Methods
	void compute(std::string p_idValue, std::string p_valueDelimeterBegin , std::string p_valueDelimeterEnd);
};

