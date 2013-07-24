#pragma once
#include "IdValue.h"

class IdValueInt : public IdValue<int>
{
public:
	// Constructor - Destructor
	IdValueInt(std::string p_idValue, std::string p_valueDelimeterBegin = "(" , std::string p_valueDelimeterEnd = ")");
	~IdValueInt(void);


protected:
	// Methods
	void compute(std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd);
};

