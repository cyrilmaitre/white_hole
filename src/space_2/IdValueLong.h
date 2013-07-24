#pragma once
#include "IdValue.h"

class IdValueLong : public IdValue<long>
{
public:
	// Constructor - Destructor
	IdValueLong(std::string p_idValue, std::string p_valueDelimeterBegin = "(" , std::string p_valueDelimeterEnd = ")");
	~IdValueLong(void);

protected:
	// Methods
	void compute(std::string p_idValue, std::string p_valueDelimeterBegin, std::string p_valueDelimeterEnd);
};

