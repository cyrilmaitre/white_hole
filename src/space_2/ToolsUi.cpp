#include "ToolsUi.h"

//******************************
// Constructor - Destructor
//******************************
ToolsUi::ToolsUi(void)
{
}
ToolsUi::~ToolsUi(void)
{
}


//******************************
// Text Tools
//******************************
std::string ToolsUi::charEntred( sf::Event myEvent )
{
	bool caps	= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	bool alt	= sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);

	switch(myEvent.key.code) // Key pressed
	{
	//******************************
	// Alpha
	//******************************
	// A
	case sf::Keyboard::A:
		if(caps)
			return "A";
		else
			return "a";
		break;

	// B
	case sf::Keyboard::B:
		if(caps)
			return "B";
		else
			return "b";
		break;

	// C
	case sf::Keyboard::C:
		if(caps)
			return "C";
		else
			return "c";
		break;

	// D
	case sf::Keyboard::D:
		if(caps)
			return "D";
		else
			return "d";
		break;

	// E
	case sf::Keyboard::E:
		if(caps)
			return "E";
		else
			return "e";
		break;

	// F
	case sf::Keyboard::F:
		if(caps)
			return "F";
		else
			return "f";
		break;

	// G
	case sf::Keyboard::G:
		if(caps)
			return "G";
		else
			return "g";
		break;

	// H
	case sf::Keyboard::H:
		if(caps)
			return "H";
		else
			return "h";
		break;

	// I
	case sf::Keyboard::I:
		if(caps)
			return "I";
		else
			return "i";
		break;

	// J
	case sf::Keyboard::J:
		if(caps)
			return "J";
		else
			return "j";
		break;

	// K
	case sf::Keyboard::K:
		if(caps)
			return "K";
		else
			return "k";
		break;

	// L
	case sf::Keyboard::L:
		if(caps)
			return "L";
		else
			return "l";
		break;

	// M
	case sf::Keyboard::M:
		if(caps)
			return "M";
		else
			return "m";
		break;

	// N
	case sf::Keyboard::N:
		if(caps)
			return "N";
		else
			return "n";
		break;

	// O
	case sf::Keyboard::O:
		if(caps)
			return "O";
		else
			return "o";
		break;

	// P
	case sf::Keyboard::P:
		if(caps)
			return "P";
		else
			return "p";
		break;

	// Q
	case sf::Keyboard::Q:
		if(caps)
			return "Q";
		else
			return "q";
		break;

	// R
	case sf::Keyboard::R:
		if(caps)
			return "R";
		else
			return "r";
		break;

	// S
	case sf::Keyboard::S:
		if(caps)
			return "S";
		else
			return "s";
		break;

	// T
	case sf::Keyboard::T:
		if(caps)
			return "T";
		else
			return "t";
		break;

	// U
	case sf::Keyboard::U:
		if(caps)
			return "U";
		else
			return "u";
		break;

	// V
	case sf::Keyboard::V:
		if(caps)
			return "V";
		else
			return "v";
		break;

	// W
	case sf::Keyboard::W:
		if(caps)
			return "W";
		else
			return "w";
		break;

	// X
	case sf::Keyboard::X:
		if(caps)
			return "X";
		else
			return "x";
		break;

	// Y
	case sf::Keyboard::Y:
		if(caps)
			return "Y";
		else
			return "y";
		break;

	// Z
	case sf::Keyboard::Z:
		if(caps)
			return "Z";
		else
			return "z";
		break;


	//******************************
	// Numerique
	//******************************
	// 0 à @
	case sf::Keyboard::Num0:
		if(caps)
			return "0";
		else if(alt)
			return "@";
		else
			return "à";
		break;

	// 1 &
	case sf::Keyboard::Num1:
		if(caps)
			return "1";
		else
			return "&";
		break;

	// 2 é ~
	case sf::Keyboard::Num2:
		if(caps)
			return "2";
		else if(alt)
			return "~";
		else
			return "é";
		break;

	// 3 " #
	case sf::Keyboard::Num3:
		if(caps)
			return "3";
		else if(alt)
			return "#";
		else
			return "\"";
		break;

	// 4 ' {
	case sf::Keyboard::Num4:
		if(caps)
			return "4";
		else if(alt)
			return "{";
		else
			return "'";
		break;

	// 5 ( [
	case sf::Keyboard::Num5:
		if(caps)
			return "5";
		else if(alt)
			return "[";
		else
			return "(";
		break;

	// 6 - |
	case sf::Keyboard::Num6:
		if(caps)
			return "6";
		else if(alt)
			return "|";
		else
			return "-";
		break;

	// 7 è `
	case sf::Keyboard::Num7:
		if(caps)
			return "7";
		else if(alt)
			return "`";
		else
			return "è";
		break;

	// 8 _ \ 
	case sf::Keyboard::Num8:
		if(caps)
			return "8";
		else if(alt)
			return "\\";
		else
			return "_";
		break;

	// 9 ç ^
	case sf::Keyboard::Num9:
		if(caps)
			return "9";
		else if(alt)
			return "^";
		else
			return "ç";
		break;


	//******************************
	// Other
	//******************************
	// ²
	case sf::Keyboard::Quote:
		return "²";
		break;

	// ) ° ]
	case sf::Keyboard::LBracket:
		if(caps)
			return "°";
		else if(alt)
			return "]";
		else
			return ")";
		break;

	// = + }
	case sf::Keyboard::Equal:
		if(caps)
			return "+";
		else if(alt)
			return "}";
		else
			return "=";
		break;

	// ^ ¨
	case sf::Keyboard::RBracket:
		if(caps)
			return "¨";
		else
			return "^";
		break;
	
	// $ £ ¤
	case sf::Keyboard::SemiColon:
		if(caps)
			return "£";
		else if(alt)
			return "¤";
		else
			return "$";
		break;

	// ù %
	case sf::Keyboard::Tilde:
		if(caps)
			return "%";
		else
			return "ù";
		break;

	// * µ
	case sf::Keyboard::BackSlash:
		if(caps)
			return "µ";
		else
			return "*";
		break;

	// , ?
	case sf::Keyboard::Comma:
		if(caps)
			return "?";
		else
			return ",";
		break;

	// ; .
	case sf::Keyboard::Period:
		if(caps)
			return ".";
		else
			return ";";
		break;

	// : /
	case sf::Keyboard::Slash:
		if(caps)
			return "/";
		else
			return ":";
		break;
	
	// Space
	case sf::Keyboard::Space:
		return " ";
		break;


	//******************************
	// NumPad
	//******************************
	// +
	case sf::Keyboard::Add:
		return "+";
		break;

	// -
	case sf::Keyboard::Subtract:
		return "-";
		break;

	// *
	case sf::Keyboard::Multiply:
		return "*";
		break;

	// /
	case sf::Keyboard::Divide:
		return "/";
		break;

	// 0
	case sf::Keyboard::Numpad0:
		return "0";
		break;

	// 1
	case sf::Keyboard::Numpad1:
		return "1";
		break;

	// 2
	case sf::Keyboard::Numpad2:
		return "2";
		break;

	// 3
	case sf::Keyboard::Numpad3:
		return "3";
		break;

	// 4
	case sf::Keyboard::Numpad4:
		return "4";
		break;

	// 5
	case sf::Keyboard::Numpad5:
		return "5";
		break;

	// 6
	case sf::Keyboard::Numpad6:
		return "6";
		break;

	// 7
	case sf::Keyboard::Numpad7:
		return "7";
		break;

	// 8
	case sf::Keyboard::Numpad8:
		return "8";
		break;

	// 9
	case sf::Keyboard::Numpad9:
		return "9";
		break;

	// Default
	default:
		return "";
	}
}
