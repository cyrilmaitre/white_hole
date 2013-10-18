#include "CharacterShipCreate.h"
#include "NetworkDefine.h"


//*************************************************************
// Define
//*************************************************************
#define RESPONSEJSON_CHARACTERSHIP		"charactership"
#define JSON_IDCHARACTERSHIP			"idCharacterShip"	


//*************************************************************
// Constructor - Destructor
//*************************************************************
CharacterShipCreate::CharacterShipCreate( CharacterShip* p_ship )
{
	this->mCharacterShip = p_ship;
}

CharacterShipCreate::~CharacterShipCreate(void)
{
}


//*************************************************************
// Methods
//*************************************************************
void CharacterShipCreate::job()
{
	if(this->mCharacterShip != NULL)
	{
		Json::Value jsonRequest = this->mCharacterShip->saveToJson();
		Json::StyledWriter writer;
		sf::Http::Response response = Network::sendJsonRequest(sf::Http::Request::Post, NETWORK_HTTP_URI_CHARACTERSHIP_CREATE, writer.write(jsonRequest));

		// Update local id
		Json::Value jsonResponse;   
		Json::Reader reader;
		bool parsingSuccessfull = reader.parse(response.getBody(), jsonResponse);
		if(parsingSuccessfull)
		{
			// Get charactership
			Json::Value jsonCharacterShip = jsonResponse.get(RESPONSEJSON_CHARACTERSHIP, NULL);
			if(jsonCharacterShip != NULL)
			{
				this->mCharacterShip->setIdCharacterShip(jsonCharacterShip.get(JSON_IDCHARACTERSHIP, -1).asLargestInt());
			}
		}

		this->setRunning(false);
	}
	else
	{
		this->setRunning(false);
	}
}

