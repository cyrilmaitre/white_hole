#include "Character.h"
#include "CharacterShip.h"
#include "FactoryGet.h"
#include "Game.h"
#include "CharacterUpdate.h"
#include "SkillCharacter.h"
#include "CharacterBank.h"


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
#define CHARACTER_JSON_CHARACTERSHIPCOUNT	"shipsCount"


//*************************************************************
// Constructor - Destructor
//*************************************************************
Character::Character(User* p_user, Json::Value json)
{
	// Init with default values
	this->mId = -1;
	this->mAvatarId = "0-0";
	this->mName = "";
	this->mRace = NULL;
	this->mJob = NULL;
	this->mUser = NULL;
	this->mSkillPoints = 0;
	this->mDateCreation = 0;
	this->mTimePlayed = 0;
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
long Character::getId()
{
	return this->mId;
}

void Character::setId( long p_id )
{
	this->mId = p_id;
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

bool Character::hasEnoughCredit( long p_credit )
{
	return this->getCredit() >= p_credit;
}

long Character::getCredit()
{
	return this->mCredit;
}

void Character::setCredit( long p_credit )
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

long Character::getTimePlayed()
{
	return this->mTimePlayed;
}

void Character::setTimePlayed( long p_time )
{
	this->mTimePlayed = p_time;
}

bool Character::isAlive()
{
	return this->mAlive;
}

void Character::setAlive( bool p_alive )
{
	this->mAlive = p_alive;
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

	this->mSkillPoints = p_points;
}

bool Character::hasSkillPoints()
{
	return this->mSkillPoints > 0;
}

SkillCharacter * Character::getSkillCharacter( int p_skillId )
{
	for(int i = 0; i < CHARACTER_SKILL_COUNT; i++)
		if(this->mSkillCharacters[i] != NULL && this->mSkillCharacters[i]->getSkill()->getId() == p_skillId)
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

CharacterShip * Character::getShipPiloted()
{
	return this->mShipPiloted;
}

void Character::setShipPiloted( CharacterShip *p_ship )
{
	this->mShipPiloted = p_ship;
}


//*************************************************************
// Methods
//*************************************************************
void Character::loadFromJson( Json::Value json )
{
	this->setId(json.get(CHARACTER_JSON_IDCHARACTER, -1).asInt());
	this->setName(json.get(CHARACTER_JSON_NAME, "").asString());
	this->setAvatarId(json.get(CHARACTER_JSON_AVATARID, "0-0").asString());
	this->setSkillPoints(json.get(CHARACTER_JSON_SKILLPOINTS, 0).asInt());
	this->setLevel(json.get(CHARACTER_JSON_LEVEL, 0).asInt());
	this->setLevelConfig(FactoryGet::getLevelFactory()->getLevelCharacter());
	this->setExperience(json.get(CHARACTER_JSON_EXPERIENCE, 0).asInt());
	this->setCredit(json.get(CHARACTER_JSON_CREDIT, 0).asInt64());
	this->setDateCreation(json.get(CHARACTER_JSON_DATECREATION, 0).asInt());
	this->setTimePlayed(json.get(CHARACTER_JSON_TIMEPLAYED, 0).asInt());
	this->setAlive(json.get(CHARACTER_JSON_ALIVE, 0).asBool());
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
}

Json::Value Character::saveToJson()
{
	Json::Value json;
	json[CHARACTER_JSON_IDCHARACTER] = this->getId();
	json[CHARACTER_JSON_NAME] = this->getName();
	json[CHARACTER_JSON_AVATARID] = this->getAvatarId();
	json[CHARACTER_JSON_SKILLPOINTS] = this->getSkillPoints();
	json[CHARACTER_JSON_LEVEL] = this->getLevel();
	json[CHARACTER_JSON_EXPERIENCE] = this->getExperience();
	json[CHARACTER_JSON_CREDIT] = this->getCredit();
	json[CHARACTER_JSON_DATECREATION] = this->getDateCreation();
	json[CHARACTER_JSON_TIMEPLAYED] = this->getTimePlayed();
	json[CHARACTER_JSON_ALIVE] = this->isAlive();
	json[CHARACTER_JSON_IDRACE] = this->getRace()->getId();
	json[CHARACTER_JSON_IDJOB] = this->getJob()->getId();
	json[CHARACTER_JSON_IDUSER] = this->getUser()->getId();
	
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

void Character::addBank( CharacterBank* p_bank )
{
	this->mBanks.push_back(p_bank);
}

void Character::incCredit( long p_inc )
{
	this->setCredit(this->getCredit() + p_inc);
	new CharacterUpdate(this);
}

void Character::decCredit( long p_dec )
{
	this->setCredit(this->getCredit() - p_dec);
	new CharacterUpdate(this);
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
	this->incSkillPoints(((LevelCharacter*)this->getLevelConfig())->getSkillPointsOnLevelUp());
	new CharacterUpdate(this);
}

void Character::incExperience( long p_inc )
{
	Levelable::incExperience(p_inc);
	new CharacterUpdate(this);
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






