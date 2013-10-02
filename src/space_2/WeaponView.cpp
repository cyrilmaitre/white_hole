#include "WeaponView.h"
#include "ToolsImage.h"
#include "SpriteParameterFactory.h"
#include "Game.h"
#include "MapObject.h"
#include "ManagerConfig.h"


//*************************************************************
// Define
//*************************************************************
#define WEAPONVIEW_BACKCOLOR					sf::Color(39, 39, 39)
#define WEAPONVIEW_BORDCOLOR					sf::Color(24, 24, 24)
#define WEAPONVIEW_BORDSIZE						2
#define WEAPONVIEW_WEAPONICON_SIZE				48
#define WEAPONVIEW_WEAPONICON_OFFSETY			6
#define WEAPONVIEW_WEAPONICON_BACKCOLOR			sf::Color(55, 55, 55)
#define WEAPONVIEW_WEAPONICON_BORDCOLOR			sf::Color(65, 65, 65)
#define WEAPONVIEW_WEAPONICON_BORDSIZE			2
#define WEAPONVIEW_AMMOICON_SIZE				16
#define WEAPONVIEW_AMMOICON_OFFSETX				WEAPONVIEW_WEAPONICON_OFFSETY
#define WEAPONVIEW_AMMOICON_OFFSETY				WEAPONVIEW_WEAPONICON_OFFSETY
#define WEAPONVIEW_AMMOICON_BACKCOLOR			sf::Color(49, 49, 49)	
#define WEAPONVIEW_AMMOICON_BORDSIZE			2
#define WEAPONVIEW_RANGEICON_SIZE				10
#define WEAPONVIEW_RANGEICON_BORDSIZE			0
#define WEAPONVIEW_RANGEICON_OFFSETX			73
#define WEAPONVIEW_RANGEICON_OFFSETY			5
#define WEAPONVIEW_ANGLEICON_SIZE				10
#define WEAPONVIEW_ANGLEICON_BORDSIZE			0
#define WEAPONVIEW_ANGLEICON_OFFSETX			73
#define WEAPONVIEW_ANGLEICON_OFFSETY			20
#define WEAPONVIEW_TB_AMMOCOUNT_FONTSIZE		12
#define WEAPONVIEW_TB_AMMOCOUNT_FONTCOLOR		sf::Color(195, 195, 195)
#define WEAPONVIEW_TB_AMMOCOUNTOUT_FONTCOLOR	sf::Color(195, 0, 0)
#define WEAPONVIEW_TB_AMMOCOUNT_OFFSETX			4
#define WEAPONVIEW_INACTIF_BACKCOLOR			sf::Color(30, 30, 30, 215)
#define WEAPONVIEW_INACTIF_TEXT_FONTSIZE		12
#define WEAPONVIEW_INACTIF_TEXT_FONTCOLOR		sf::Color(235, 235, 235)
#define WEAPONVIEW_WEAPONINFO_WIDTH				200
#define WEAPONVIEW_AMMOINFO_WIDTH				200
#define WEAPONVIEW_RANGEINFO_WIDTH				115
#define WEAPONVIEW_ANGLEINFO_WIDTH				115
#define WEAPONVIEW_RELOAD_BACKCOLOR				sf::Color(235, 235, 235, 45)
#define WEAPONVIEW_RELOAD_FIRERATE_MIN			0.5


//*************************************************************
// Constructor - Destructor
//*************************************************************
WeaponView::WeaponView( Weapon *p_weapon )
{
	this->mWeapon = NULL;

	this->setMouseOverForced(true);
	this->setSize(WEAPONVIEW_WIDTH, WEAPONVIEW_HEIGHT);
	this->setBackgroundColor(WEAPONVIEW_BACKCOLOR, true);
	this->setBorderColor(WEAPONVIEW_BORDCOLOR, true);
	this->setBorderSize(WEAPONVIEW_BORDSIZE, true);
	this->setVisible(false);

	this->mWeaponIcon.setWidth(WEAPONVIEW_WEAPONICON_SIZE);
	this->mWeaponIcon.setHeight(WEAPONVIEW_WEAPONICON_SIZE);
	this->mWeaponIcon.setBackgroundColor(WEAPONVIEW_WEAPONICON_BACKCOLOR, true);
	this->mWeaponIcon.setBorderColor(WEAPONVIEW_WEAPONICON_BORDCOLOR, true);
	this->mWeaponIcon.setBorderSize(WEAPONVIEW_WEAPONICON_BORDSIZE, true);

	this->mAmmoIcon.setWidth(WEAPONVIEW_AMMOICON_SIZE);
	this->mAmmoIcon.setHeight(WEAPONVIEW_AMMOICON_SIZE);
	this->mAmmoIcon.setBackgroundColor(WEAPONVIEW_AMMOICON_BACKCOLOR, true);
	this->mAmmoIcon.setBorderSize(WEAPONVIEW_AMMOICON_BORDSIZE, true);
	this->mAmmoCount.setFontSize(WEAPONVIEW_TB_AMMOCOUNT_FONTSIZE);
	this->mAmmoCount.setFontColor(WEAPONVIEW_TB_AMMOCOUNT_FONTCOLOR);

	this->mRangeIcon.setWidth(WEAPONVIEW_RANGEICON_SIZE);
	this->mRangeIcon.setHeight(WEAPONVIEW_RANGEICON_SIZE);
	this->mRangeIcon.setBorderSize(WEAPONVIEW_RANGEICON_BORDSIZE);

	this->mAngleIcon.setWidth(WEAPONVIEW_ANGLEICON_SIZE);
	this->mAngleIcon.setHeight(WEAPONVIEW_ANGLEICON_SIZE);
	this->mAngleIcon.setBorderSize(WEAPONVIEW_ANGLEICON_BORDSIZE);

	this->mInactifShape.setFillColor(WEAPONVIEW_INACTIF_BACKCOLOR);
	this->mInactifText.setFontSize(WEAPONVIEW_INACTIF_TEXT_FONTSIZE);
	this->mInactifText.setFontColor(WEAPONVIEW_INACTIF_TEXT_FONTCOLOR);
	this->mInactifText.setText(Resource::resource->getBundle()->getString("inactive"));

	this->mWeaponInfo = new PopupBubble(&this->mWeaponIcon);
	this->mAmmoInfo = new PopupBubble(&this->mAmmoIcon);
	this->mRangeInfo = new PopupBubble(&this->mRangeIcon);
	this->mAngleInfo = new PopupBubble(&this->mAngleIcon);

	// Bubble range
	this->mRangeInfo->setText(	Resource::resource->getBundle()->getString("uiRangeInfo"));

	// Bubble angle
	this->mAngleInfo->setText(	Resource::resource->getBundle()->getString("uiAngleInfo"));

	this->setWeapon(p_weapon);
	this->updateAmmoCount();
	this->updateAmmoIcon();
	this->updateAngle();
	this->updateRange();
	this->notifyPositionChanged();
	this->notifySizeChanged();
}

WeaponView::~WeaponView(void)
{
	delete this->mWeaponInfo;
	delete this->mAmmoInfo;
	delete this->mRangeInfo;
	delete this->mAngleInfo;
}


//*************************************************************
// Getters - Setters
//*************************************************************
Weapon * WeaponView::getWeapon()
{
	return this->mWeapon;
}

void WeaponView::setWeapon( Weapon *p_weapon )
{
	if(this->mWeapon != p_weapon)
	{
		this->mWeapon = p_weapon;
		this->notifyWeaponChanged();
	}
}


//*************************************************************
// Methods
//*************************************************************
void WeaponView::update( sf::Event p_event )
{
	if(this->isVisible())
	{
		// Update ui
		this->mWeaponIcon.update(p_event);
		this->mWeaponInfo->update(p_event);

		if(this->mWeapon->getAmmo() != NULL)
		{
			this->mAmmoIcon.update(p_event);
			this->mAmmoInfo->update(p_event);
		}

		this->mRangeIcon.update(p_event);
		this->mRangeInfo->update(p_event);

		this->mAngleIcon.update(p_event);
		this->mAngleInfo->update(p_event);

		// Update block
		Block::update(p_event);

		// Update actif
		if(this->isClicked())
			this->mWeapon->setActif(!this->mWeapon->isActif());
	}
}

void WeaponView::update()
{
	if(this->isVisible())
	{
		this->mWeaponInfo->update();
		this->mAmmoInfo->update();
		this->mRangeInfo->update();
		this->mAngleInfo->update();

		if(this->getWeapon()->isAmmoChanged())
			this->updateAmmoIcon();

		if(this->getWeapon()->isAmmoCountChanged())
			this->updateAmmoCount();

		if(this->getWeapon()->isRangeOkChanged())
			this->updateRange();

		if(this->getWeapon()->isAngleOkChanged())
			this->updateAngle();
	}
}

void WeaponView::updateAmmoIcon()
{
	if(this->mWeapon != NULL && this->mWeapon->getAmmo() != NULL)
	{
		this->mAmmoIcon.setBorderColor(ToolsImage::hexaToColor(this->getWeapon()->getAmmo()->getAmmoType()->getColor()), true);
		this->mAmmoIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->getWeapon()->getAmmo()->getSpriteId()), true);
	}
}

void WeaponView::updateAmmoCount()
{
	if(this->mWeapon != NULL)
	{
		if(this->mWeapon->getAmmo() != NULL)
		{
			this->mAmmoCount.setText(Tools::buildStringWithInt(this->getWeapon()->getAmmoCount()) + "/" + Tools::buildStringWithInt(this->getWeapon()->getWeaponModel()->getAmmoMax()));
			if(this->mWeapon->getAmmoCount() == 0)
				this->mAmmoCount.setFontColor(WEAPONVIEW_TB_AMMOCOUNTOUT_FONTCOLOR);
			else
				this->mAmmoCount.setFontColor(WEAPONVIEW_TB_AMMOCOUNT_FONTCOLOR);
		}
		else
		{
			this->mAmmoCount.setText("0/" + Tools::buildStringWithInt(this->getWeapon()->getWeaponModel()->getAmmoMax()));
			this->mAmmoCount.setFontColor(WEAPONVIEW_TB_AMMOCOUNTOUT_FONTCOLOR);
		}
	}
	this->updateAmmoCountPosition();
}

void WeaponView::updateRange()
{
	if(this->mWeapon != NULL && this->mWeapon->isRangeOk())
		this->mRangeIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon10X10()->getSpritePtr(IC_10X10_WEAPON_OK), true);
	else
		this->mRangeIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon10X10()->getSpritePtr(IC_10X10_WEAPON_NOK), true);
}

void WeaponView::updateAngle()
{
	if(this->mWeapon != NULL && this->mWeapon->isAngleOk())
		this->mAngleIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon10X10()->getSpritePtr(IC_10X10_WEAPON_OK), true);
	else
		this->mAngleIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterIcon10X10()->getSpritePtr(IC_10X10_WEAPON_NOK), true);
}

void WeaponView::updateAmmoCountPosition()
{
	this->mAmmoCount.setPosition(	this->mAmmoIcon.getRightX() + (this->getWidth() - this->mAmmoIcon.getWidth() - WEAPONVIEW_AMMOICON_OFFSETX - this->mAmmoCount.getWidth()) / 2,
									this->mAmmoIcon.getY() + (this->mAmmoIcon.getHeight() - this->mAmmoCount.getHeight()) / 2);
}

void WeaponView::draw()
{
	if(this->isVisible())
	{
		// Draw block
		Block::draw();

		// Draw ui
		this->mWeaponIcon.draw();
		this->mAmmoIcon.draw();
		this->mAmmoCount.draw();
		this->mRangeIcon.draw();
		this->mAngleIcon.draw();

		// Draw reload
		if(this->mWeapon->isActif())
			this->drawReloading();

		// Draw inactif
		if(!this->mWeapon->isActif())
		{
			Resource::resource->getApp()->draw(this->mInactifShape);
			this->mInactifText.draw();
		}
	}
}

void WeaponView::notifyWeaponChanged()
{
	if(this->mWeapon != NULL)
	{
		this->mWeaponIcon.setBackgroundImage(SpriteParameterFactory::getSpriteParameterItems()->getSpritePtr(this->mWeapon->getWeaponModel()->getSpriteId()), true);

		// Bubble Weapon
		this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoName") + 
			":" + Tools::getSpaceAfterColon() + this->getWeapon()->getWeaponModel()->getName(), false);

		if(this->getWeapon()->getWeaponModel()->getItemType()->hasParent())
			this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoType") + 
				":" + Tools::getSpaceAfterColon() + this->getWeapon()->getWeaponModel()->getItemType()->getParent()->getName() + " " + this->getWeapon()->getWeaponModel()->getItemType()->getName(), false);
		else
			this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoType") + 
				":" + Tools::getSpaceAfterColon() + this->getWeapon()->getWeaponModel()->getItemType()->getName(), false);

		this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoRange") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getWeapon()->getWeaponModel()->getRange()) + " " + Resource::resource->getBundle()->getString("meterAb"), false);
		this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoAngle") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithInt(this->getWeapon()->getWeaponModel()->getRangeAngle()) + " " + Resource::resource->getBundle()->getString("degreesAb"), false);
		this->mWeaponInfo->addLine(	Resource::resource->getBundle()->getString("uiWeaponInfoDps") + 
			":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getWeapon()->getDps()), false);
		this->mWeaponInfo->notifyDataSetChanged();

		// Bubble Ammo
		if(this->mWeapon->getAmmo())
		{
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoName") + 
				":" + Tools::getSpaceAfterColon() + this->getWeapon()->getAmmo()->getName(), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoType") + 
				":" + Tools::getSpaceAfterColon() + this->getWeapon()->getAmmo()->getAmmoType()->getName(), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoShieldMultiplier") + 
				":" + Tools::getSpaceAfterColon() + Tools::buildStringWithFloat(this->getWeapon()->getAmmo()->getAmmoType()->getDamageShieldMultiplier()), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoArmorMultiplier") + 
				":" + Tools::getSpaceAfterColon() + Tools::buildStringWithFloat(this->getWeapon()->getAmmo()->getAmmoType()->getDamageArmorMultiplier()), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoStructureMultiplier") + 
				":" + Tools::getSpaceAfterColon() + Tools::buildStringWithFloat(this->getWeapon()->getAmmo()->getAmmoType()->getDamageStructureMultiplier()), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoDamage") + 
				":" + Tools::getSpaceAfterColon() + Tools::buildStringWithDouble(this->getWeapon()->getAmmo()->getDamage()), false);
			this->mAmmoInfo->addLine(	Resource::resource->getBundle()->getString("uiAmmoInfoSplash") + 
				":" + Tools::getSpaceAfterColon() + (this->getWeapon()->getAmmo()->getSplashRadius() > 0 ? Resource::resource->getBundle()->getString("yes") : Resource::resource->getBundle()->getString("no")), false);
			this->mAmmoInfo->notifyDataSetChanged();
		}

		this->updateAmmoCount();
		this->updateAmmoIcon();
		this->updateAngle();
		this->updateRange();
	}
	this->setVisible(this->mWeapon != NULL);
}

void WeaponView::notifyPositionChanged()
{
	Block::notifyPositionChanged();
	this->mWeaponIcon.setPosition(	this->getX() + (this->getWidth() - this->mWeaponIcon.getWidth()) / 2,
									this->getY() +  WEAPONVIEW_WEAPONICON_OFFSETY);

	this->mAmmoIcon.setPosition(	this->getX() + WEAPONVIEW_AMMOICON_OFFSETX,
									this->getY() + this->getHeight() - this->mAmmoIcon.getHeight() - WEAPONVIEW_AMMOICON_OFFSETY);
	this->updateAmmoCountPosition();

	this->mInactifShape.setPosition(this->getX(), this->getY());
	this->mInactifText.setPosition(	this->getX() + (this->getWidth() - this->mInactifText.getWidth()) / 2,
									this->getY() + (this->getHeight() - this->mInactifText.getHeight()) / 2);

	this->mRangeIcon.setPosition(this->getX() + WEAPONVIEW_RANGEICON_OFFSETX, this->getY() + WEAPONVIEW_RANGEICON_OFFSETY);
	this->mAngleIcon.setPosition(this->getX() + WEAPONVIEW_ANGLEICON_OFFSETX, this->getY() + WEAPONVIEW_ANGLEICON_OFFSETY);
}

void WeaponView::notifySizeChanged()
{
	Block::notifySizeChanged();
	this->mInactifShape.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
}

void WeaponView::drawReloading()
{
	float reloadingPercent = 1;
	if(this->getWeapon()->isReloading())
		reloadingPercent = 1 - (this->getWeapon()->getReloadTime() / this->getWeapon()->getWeaponModel()->getReloadingSpeed());
	else if(this->getWeapon()->isFiring() && this->getWeapon()->getWeaponModel()->getFireRate() >= WEAPONVIEW_RELOAD_FIRERATE_MIN)
		reloadingPercent = 1 - (this->getWeapon()->getFireRateTime() / this->getWeapon()->getWeaponModel()->getFireRate());
	else
		return;
	ToolsImage::drawReloadPolygon(reloadingPercent, this, WEAPONVIEW_RELOAD_BACKCOLOR);
}


