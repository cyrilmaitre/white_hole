#pragma once
#include "FieldSet.h"
#include "TextBox.h"


class MarketItemStockView : public FieldSet
{
public:
	// Constructor - Destructor
	MarketItemStockView(void);
	~MarketItemStockView(void);

	// Getters - Setters
	void setIndice(float p_indice);

	// Methods
	void updatePosition();
	void update(sf::Event p_event);
	void draw();
	void notifyPositionChanged();
	void notifyItemStockChanged();


private:
	// Attributs
	FieldSet mFieldsetIndice;
	TextBox mTBIndiceLabel;
	TextBox mTBIndice;
};

