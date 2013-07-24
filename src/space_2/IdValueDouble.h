#pragma once
#include "IdValue.h"

class IdValueDouble : public IdValue<double>
{
public:
	// Constructor - Destructor
	IdValueDouble(std::string p_idValue, std::string p_valueDelimeterBegin = "(" , std::string p_valueDelimeterEnd = ")");
	~IdValueDouble(void);


protected:
	// Methods
	void compute(std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd);
};

