#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EventManager.h"
#include "IdGenerator.h"

class View;

class Object
{
public:
	// Constructor - Destructor
	Object();
	~Object();

	// Getters - Setters
	long getObjectId();

	virtual double getX();
	virtual double getX(Object *p_parentObject);
	virtual void setX(double p_x, bool p_notify = true);
	virtual void setX(double p_x, Object *p_parentObject);
	virtual double getY();
	virtual double getY(Object *p_parentObject);
	virtual void setY(double p_y, bool p_notify = true);
	virtual void setY(double p_y, Object *p_parentObject);
	virtual void setPosition(double p_x, double p_y, bool p_notify = true);
	
	double getCenterX();
	double getLeftX();
	double getRightX();
	double getCenterY();
	double getTopY();
	double getBottomY();

	int getWidth();
	int getWidthHalf();
	virtual void setWidth(int p_witdh);
	int getHeight();
	int getHeightHalf();
	virtual void setHeight(int p_height);
	virtual void setSize(int p_witdh, int p_height);
	int getArea();
	void setArea(int p_area);

	bool isVisible();
	virtual void setVisible(bool p_visible);

	bool hasMouseOver();
	bool isUpdateMouseOver();
	void setUpdateMouseOver(bool p_param);

	bool isMouseOverForced();
	void setMouseOverForced(bool p_forced);

	View* getView();
	void setView(View* p_view);

	bool isEnable();
	void setEnable(bool p_enable);

	bool isPositionChanged();
	bool isSizeChanged();
	bool isMouseOverChanged();
	bool isEnableChanged();
	bool isVisibleChanged();


protected:
	// Attributs
	double mX;
	double mY;
	int mWidth;
	int mHeight;
	int mArea;
	View *mView;
	bool mMouseOver;
	bool mMouseOverForced;
	bool mUpdateMouseOver;
	bool mEnable;
	bool mVisible;
	bool mPositionChanged;
	bool mSizeChanged;
	bool mMouseOverChanged;
	bool mEnableChanged;
	bool mVisibleChanged;

	// Methods
	virtual void notifyPositionChanged();
	virtual void notifySizeChanged();
	virtual void notifyMouseOverChanged();
	virtual void notifyEnableChanged();
	virtual void notifyVisibleChanged();
	void update(sf::Event p_event);


private:
	// Attributes
	long mObjectId;

	// Methods
	virtual void updateMouseOver();

	// Static
	static IdGenerator mIdGenerator;
};


