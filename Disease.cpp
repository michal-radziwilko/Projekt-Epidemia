#include "Person.h"
#include "Disease.h"
#include <iostream>

using namespace std;

string CommonDisease::description()
{
	return "Common Disease nr: " + to_string(diseaseID()) + "  Health: " + to_string(diseaseHP()) + "\n"
		+ "Attack chance: " + to_string(_attackChance) + "\n";
}

string UltraVegan::description()
{
	return "Ultra Vegan nr: " + to_string(diseaseID()) + "  Health: " + to_string(diseaseHP()) + "\n"
		+ "Attack chance: " + to_string(_attackChance) + "\n";
}

string Mutagen::description()
{
	return "Mutagen nr: " + to_string(diseaseID()) + "  Health: " + to_string(diseaseHP()) + "\n"
		+ "Attack chance: " + to_string(_attackChance) + "  Attack count: " + to_string(_attackCount) + "\n";
}

bool CommonDisease::tryAttack()
{
	if (rand() % 100 + 1 <= _attackChance) return true;
	else return false;
}

bool UltraVegan::tryAttack()
{
	if (rand() % 100 + 1 <= _attackChance) return true;
	else return false;
}

bool Mutagen::tryAttack()
{
	bool atk = false;
	for (int i = 0; i<_attackCount; i++)
	{
		if (rand() % 100 + 1 <= _attackChance) atk = true;
	}
	return atk;
}