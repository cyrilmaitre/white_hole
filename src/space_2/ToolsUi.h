#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ToolsUi
{
public:
	// Methods
	static std::string charEntred(sf::Event myEvent);

		
private:
	// Constructor - Destructor
	ToolsUi(void);
	~ToolsUi(void);
};
