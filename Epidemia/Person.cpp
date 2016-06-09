#include "Person.h"
#include <iostream>

using namespace std;

string CommonPerson::description()
{
	return "Common Person nr: " + to_string(personID()) + "  Health: " + to_string(personHP()) + "\n"
		+ "Attack: " + to_string(_attack) + "  Attack chance: " + to_string(_attackChance) + "  Dodge chance: " + to_string(_dodgeChance) + "\n";
}

string Scientist::description()
{
	return "Scientist nr: " + to_string(personID()) + "  Health: " + to_string(personHP()) + "\n"
		+ "Intelligence: " + to_string(_intelligence) + "\n";
}

string Vegan::description()
{
	return "Vegans nr: " + to_string(personID()) + "  Health: " + to_string(personHP()) + "\n"
		+ "Attack: " + to_string(_attack) + "  Attack chance: " + to_string(_attackChance) + "  Dodge chance: " + to_string(_dodgeChance) + "\n";
}