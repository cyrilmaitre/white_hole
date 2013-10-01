#include "Character.h"
#include "CharacterShip.h"
#include "FactoryGet.h"
#include "Game.h"
#include "CharacterUpdate.h"
#include "SkillCharacter.h"
#include "CharacterBank.h"
#include "NetworkJobManager.h"


//*************************************************************
// Define
//*************************************************************
#define CHARACTER_JSON_IDCHARACTER			"idCharacter"
#define CHARACTER_JSON_NAME					"name"
#define CHARACTER_JSON_AVATARID				"avatarId"
#define CHARACTER_JSON_SKILLPOINTS			"skillPoints"
#define CHARACTER_JSON_LEVEL				"level"
#define CHARACTER_JSON_EXPERIENCE			"experience"
#define CHARACTER_JSON_CREDIT				"credit"
#define CHARACTER_JSON_DATECREATION			"dateCreation"
#define CHARACTER_JSON_TIMEPLAYED			"timePlayed"
#define CHARACTER_JSON_ALIVE				"alive"
#define CHARACTER_JSON_IDRACE				"idRace"
#define CHARACTER_JSON_IDJOB				"idJob"
#define CHARACTER_JSON_IDUSER				"idUser"
#define CHARACTER_JSON_CHARACTERSKILLS		"skills"
#define CHARACTER_JSON_CHARACTERSHIP		"ships"
#define JSON_CHARACTERBANKS					"banks"
#define JSON_HANGARSPACE					"hangarSpace"
#define CHARACTER_JSON_CHARACTERSHIPCOUNT	"shipsCount"
#define UPDATE_TIMEPLAYED_TICK				10		// Sec
#define PERCENTAGE_XP_FOR_SHIP				0.5		// Percent


//*************************************************************
// Constructor - Destructor
//*************************************************************
Character::Character(User* p_user, Json::Value json)
{
	// Init with default values
	this->mLoaded = false;
	this->mIdCharacter = -1;
	this->mAvatarId = "0-0";
	this->mName = "";
	this->mRace = NULL;
	this->mJob = NULL;
	this->mUser = NULL;
	this->mSkillPoints = 0;
	this->mDateCreation = 0;
	this->mTimePlayed = 0;
	this->mTimeBuffer = 0;
	this->mCredit = 0;
	this->mAlive = true;
	this->mShipPiloted = NULL;

	// Init User
	this->mUser = p_user;

	// Init skills
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		this->mSkillCharacters[i] = NULL;

	// Init with json
	if(json != NULL)
		this->loadFromJson(json);
}

Character::~Character(void)
{
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		if(this->mSkillCharacters[i] != NULL)
			delete this->mSkillCharacters[i];

	for(int i = 0; i < this->mBanks.size(); i++)
	{
		if(this->mBanks[i] != NULL)
			delete this->mBanks[i];
	}
	this->mBanks.clear();

	this->destroyShips();
}

void Character::destroyShips()
{
	for(int i = 0; i < this->getShipCount(); i++)
	{
		delete this->mShips[i];
		this->mShips[i] = NULL;
	}
	this->mShips.clear();
	this->mShipPiloted = NULL;
}


//*************************************************************
// Getters - Setters
//*************************************************************
long Character::getIdCharacter()
{
	return this->mIdCharacter;
}

void Character::setIdCharacter( long p_id )
{
	this->mIdCharacter = p_id;
}

std::string Character::getName()
{
	return this->mName;
}

void Character::setName( std::string p_name )
{
	this->mName = p_name;
}

std::string Character::getAvatarId()
{
	return this->mAvatarId;
}

void Character::setAvatarId( std::string p_id )
{
	this->mAvatarId = p_id;
}

bool Character::hasEnoughCredit( double p_credit )
{
	return this->getCredit() >= p_credit;
}

double Character::getCredit()
{
	return this->mCredit;
}

void Character::setCredit( double p_credit )
{
	this->mCredit = p_credit;
}

long Character::getDateCreation()
{
	return this->mDateCreation;
}

void Character::setDateCreation( long p_date )
{
	this->mDateCreation = p_date;
}

long Character::getTimePlayedReal()
{
	return this->mTimePlayed + this->mTimeBuffer;
}

long Character::getTimePlayed()
{
	return this->mTimePlayed;
}

void Character::setTimePlayed( long p_time )
{
	if(this->mTimePlayed != p_time)
	{
		this->mTimePlayed = p_time;
		this->notifyTimePlayedChanged();
	}
}

bool Character::isAlive()
{
	return this->mAlive;
}

void Character::setAlive( bool p_alive )
{
	this->mAlive = p_alive;
}

bool Character::hasHangarSpaceFree()
{
	return this->getHangarSpaceFree() > 0;
}

int Character::getHangarSpaceOccuped()
{
	return this->getShipCount();
}

int Character::getHangarSpaceFree()
{
	return this->getHangarSpace() - this->getHangarSpaceOccuped();
}

int Character::getHangarSpace()
{
	return this->mHangarSpace;
}

void Character::setHangarSpace( int p_space )
{
	if(this->mHangarSpace != p_space)
	{
		this->mHangarSpace = p_space;
		this->notifyHangarSpaceChanged();
	}
}

User* Character::getUser()
{
	return this->mUser;
}

void Character::setUser( User *p_user )
{
	this->mUser = p_user;
}

Race* Character::getRace()
{
	return this->mRace;
}

void Character::setRace( Race* p_race )
{
	this->mRace = p_race;
}

bool Character::hasRace()
{
	return this->mRace != NULL;
}

Job* Character::getJob()
{
	return this->mJob;
}

void Character::setJob( Job* p_job )
{
	this->mJob = p_job;
}

bool Character::hasJob()
{
	return this->mJob != NULL;
}

int Character::getSkillPoints()
{
	return this->mSkillPoints;
}

void Character::setSkillPoints( int p_points )
{
	if(p_points < 0)
		p_points = 0;

	if(this->mSkillPoints != p_points)
	{
		this->mSkillPoints = p_points;
		this->notifySkillPointsChanged();
	}
}

bool Character::hasSkillPoints()
{
	return this->mSkillPoints > 0;
}

SkillCharacter * Character::getSkillCharacter( int p_skillId )
{
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		if(this->mSkillCharacters[i] != NULL && this->mSkillCharacters[i]->getSkill()->getIdSkill() == p_skillId)
			return this->mSkillCharacters[i];
}

SkillCharacter * Character::getSkillCharacterByIndex( int index )
{
	if(index >= 0 && index < CHARACTER_SKILL_COUNT)
		return this->mSkillCharacters[index];
	else
		return NULL;
}

int Character::getBankCount()
{
	return this->mBanks.size();
}

CharacterBank* Character::getBank( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getBankCount())
		p_index = this->getBankCount() - 1;

	return this->mBanks[p_index];
}

CharacterBank* Character::getBankByNumber( int p_number )
{
	CharacterBank* currentBank = this->getBank(p_number - 1);
	if(currentBank != NULL && currentBank->getNumber() == p_number)
		return currentBank;

	for(int i = 0; i < this->getBankCount(); i++)
	{
		if(this->mBanks[i]->getNumber() == p_number)
			return this->mBanks[i];
	}

	return NULL;
}

int Character::getShipCount()
{
	return this->mShips.size();
}

CharacterShip * Character::getShip( int p_index )
{
	if(p_index < 0)
		p_index = 0;
	else if(p_index >= this->getShipCount())
		p_index = this->getShipCount() - 1;

	return this->mShips[p_index];
}

CharacterShip* Character::getShipPiloted()
{
	return this->mShipPiloted;
}

void Character::setShipPiloted( CharacterShip* p_ship )
{
	if(this->mShipPiloted != p_ship)
	{
		if(this->mShipPiloted != NULL)
			this->mShipPiloted->setPiloted(false);

		this->mShipPiloted = p_ship;
		if(this->mShipPiloted != NULL)
			this->mShipPiloted->setPiloted(true);
	}
}


//*************************************************************
// Methods
//*************************************************************
void Character::init()
{
	this->mTimeBufferClock.restart();
}

void Character::update()
{
	this->updateTime();
}

void Character::updateTime()
{
	this->mTimeBuffer += this->mTimeBufferClock.getElapsedTimeAsSeconds();
	this->mTimeBufferClock.restart();
	if(this->mTimeBuffer > UPDATE_TIMEPLAYED_TICK)
	{
		this->setTimePlayed(this->getTimePlayed() + UPDATE_TIMEPLAYED_TICK);
		this->mTimeBuffer -= UPDATE_TIMEPLAYED_TICK;
	}
}

void Character::loadFromJson( Json::Value json )
{
	this->mLoaded = false;
	this->setIdCharacter(json.get(CHARACTER_JSON_IDCHARACTER, -1).asInt());
	this->setName(json.get(CHARACTER_JSON_NAME, "").asString());
	this->setAvatarId(json.get(CHARACTER_JSON_AVATARID, "0-0").asString());
	this->setSkillPoints(json.get(CHARACTER_JSON_SKILLPOINTS, 0).asInt());
	this->setLevel(json.get(CHARACTER_JSON_LEVEL, 0).asInt());
	this->setLevelConfig(FactoryGet::getLevelFactory()->getLevelCharacter());
	this->setExperience(json.get(CHARACTER_JSON_EXPERIENCE, 0).asInt());
	this->setCredit(json.get(CHARACTER_JSON_CREDIT, 0).asDouble());
	this->setDateCreation(json.get(CHARACTER_JSON_DATECREATION, 0).asInt());
	this->setTimePlayed(json.get(CHARACTER_JSON_TIMEPLAYED, 0).asInt());
	this->setAlive(json.get(CHARACTER_JSON_ALIVE, 0).asBool());
	this->setHangarSpace(json.get(JSON_HANGARSPACE, 0).asInt());
	this->setRace(FactoryGet::getRaceFactory()->getRace(json.get(CHARACTER_JSON_IDRACE, 0).asInt()));
	this->setJob(FactoryGet::getJobFactory()->getJob(json.get(CHARACTER_JSON_IDJOB, 0).asInt()));
	
	// Skills
	Json::Value jsonSkills = json.get(CHARACTER_JSON_CHARACTERSKILLS, NULL);
	if(jsonSkills != NULL)
	{
		for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
			this->mSkillCharacters[i] = new SkillCharacter(jsonSkills[i], this);
	}

	// Banks
	Json::Value jsonBanks = json.get(JSON_CHARACTERBANKS, NULL);
	if(jsonBanks != NULL)
	{
		for(int i = 0; i < jsonBanks.size(); i++)
		{
			CharacterBank* currentBank = new CharacterBank(jsonBanks.get(i, NULL), this);
			this->addBank(currentBank);
		}
	}
	
	// Ships
	this->destroyShips();
	int shipCount = json.get(CHARACTER_JSON_CHARACTERSHIPCOUNT, 0).asInt();
	Json::Value jsonShips = json.get(CHARACTER_JSON_CHARACTERSHIP, NULL);
	if(jsonShips != NULL)
	{
		for(int i = 0; i < shipCount; i++)
		{
			CharacterShip* currentShip = new CharacterShip(jsonShips.get(i, NULL), this);
			this->addShip(currentShip);
			if(currentShip != NULL && currentShip->isPiloted())
				this->setShipPiloted(currentShip);
		}
	}
	this->mLoaded = true;
}

Json::Value Character::saveToJson()
{
	Json::Value json;
	json[CHARACTER_JSON_IDCHARACTER] = this->getIdCharacter();
	json[CHARACTER_JSON_NAME] = this->getName();
	json[CHARACTER_JSON_AVATARID] = this->getAvatarId();
	json[CHARACTER_JSON_SKILLPOINTS] = this->getSkillPoints();
	json[CHARACTER_JSON_LEVEL] = this->getLevel();
	json[CHARACTER_JSON_EXPERIENCE] = this->getExperience();
	json[CHARACTER_JSON_CREDIT] = this->getCredit();
	json[CHARACTER_JSON_DATECREATION] = this->getDateCreation();
	json[CHARACTER_JSON_TIMEPLAYED] = this->getTimePlayed();
	json[CHARACTER_JSON_ALIVE] = this->isAlive();
	json[JSON_HANGARSPACE] = this->getHangarSpace();
	json[CHARACTER_JSON_IDRACE] = this->getRace()->getIdRace();
	json[CHARACTER_JSON_IDJOB] = this->getJob()->getIdJob();
	json[CHARACTER_JSON_IDUSER] = this->getUser()->getIdUser();
	
	// Skills
	Json::Value jsonSkills;
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		jsonSkills[i] = this->mSkillCharacters[i]->saveToJson();
	json[CHARACTER_JSON_CHARACTERSKILLS] = jsonSkills;

	// Banks
	Json::Value jsonBanks;
	for(int i = 0; i < this->mBanks.size(); i++)
		jsonBanks[i] = this->mBanks[i]->saveToJson();
	json[JSON_CHARACTERBANKS] = jsonBanks;

	// Ships
	json[CHARACTER_JSON_CHARACTERSHIPCOUNT] = this->getShipCount();
	Json::Value jsonShip;
	for(int i = 0; i < this->getShipCount(); i++)
		jsonShip[i] = this->mShips[i]->saveToJson();
	json[CHARACTER_JSON_CHARACTERSHIP] = jsonShip;
	
	return json;
}

void Character::addShip(CharacterShip* p_ship)
{
	this->mShips.push_back(p_ship);
}

void Character::removeShip( CharacterShip* p_ship )
{
	for(int i = 0; i < this->mShips.size(); i++)
	{
		if(this->mShips[i]->getIdCharacterShip() == p_ship->getIdCharacterShip())
		{
			this->mShips.erase(this->mShips.begin() + i);
			break;
		}
	}
}

void Character::addBank( CharacterBank* p_bank )
{
	this->mBanks.push_back(p_bank);
}

void Character::incCredit( double p_inc )
{
	this->setCredit(this->getCredit() + p_inc);
}

void Character::decCredit( double p_dec )
{
	this->setCredit(this->getCredit() - p_dec);
}

void Character::incSkillPoints()
{
	this->incSkillPoints(1);
}

void Character::incSkillPoints( int p_inc )
{
	this->setSkillPoints(this->getSkillPoints() + p_inc);
}

void Character::decSkillPoints()
{
	this->setSkillPoints(this->getSkillPoints() - 1);
}

void Character::incLevel()
{
	Levelable::incLevel();
	this->incSkillPoints((this->getLevelConfig())->getSkillPointsOnLevelUp());
}

void Character::incExperience( long p_inc )
{
	long xpForShip = (long)((float)p_inc * PERCENTAGE_XP_FOR_SHIP);
	long xpForCharacter = p_inc - xpForShip;
	Levelable::incExperience(xpForCharacter);
	this->getShipPiloted()->incExperience(xpForShip);
}

void Character::incHangarSpace()
{
	this->setHangarSpace(this->getHangarSpace() + 1);
}

void Character::createBase()
{
	this->mSkillCharacters[0] =	new SkillCharacter(FactoryGet::getSkillFactory()->getSkillFighting(), this);
	this->mSkillCharacters[1] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillDrone(), this);
	this->mSkillCharacters[2] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillSteering(), this);
	this->mSkillCharacters[3] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillMining(), this);
	this->mSkillCharacters[4] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillCrafting(), this);
	this->mSkillCharacters[5] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillAlchemy(), this);
	this->mSkillCharacters[6] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillBargaining(), this);
	this->mSkillCharacters[7] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillSalvaging(), this);
	this->mSkillCharacters[8] = new SkillCharacter(FactoryGet::getSkillFactory()->getSkillConstruction(), this);
}

void Character::notifyTimePlayedChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}

void Character::notifySkillPointsChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}

void Character::notifyHangarSpaceChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}

void Character::notifyExperienceChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}

void Character::notifyLevelChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}

void Character::notifyCreditChanged()
{
	if(this->mLoaded)
		NetworkJobManager::getInstance()->addJob(new CharacterUpdate(this));
}




