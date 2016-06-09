#include "Country.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int Country::persons()
{
	return vectorOfPersons.size();
}

int Country::infectedPersons()
{
	return vectorOfInfectedPersons.size();
}

int Country::cure()
{
	return _cure;
}

void Country::InfectPerson(std::vector<Person *>::iterator personOpponent)
{
	vectorOfPersons.erase(personOpponent);
	int r = rand() % 10 + 1;
	if (r <= 8)  vectorOfInfectedPersons.push_back(new CommonDisease);
	if (r == 9)  vectorOfInfectedPersons.push_back(new UltraVegan);
	if (r == 10)  vectorOfInfectedPersons.push_back(new Mutagen);
}

Country::Country(unsigned int population, int sl, int vl, int zl)
{
	_cure = 10000;
	_PersonPower = rand() % 11 - 5;
	_PersonImmuneSystem = rand() % 11 - 5;
	_LackOfHygiene = rand() % 7 - 3;//od-3 do 3 roznicy w spreadVirus
	_scientists = 0; _vegans = 0; _commons = 0;
	_scienceLevel = sl;
	_veganLevel = vl;
	int r, h = population - zl, c = h - sl - vl;
	for (int i = 0; i<c; i++)
	{
		vectorOfPersons.push_back(new CommonPerson);
		_commons++;
	}
	for (int i = 0; i<sl; i++)
	{
		r = rand() % vectorOfPersons.size();
		vectorOfPersons.insert(vectorOfPersons.begin() + r, new Scientist);
		_scientists++;
	}
	for (int i = 0; i<vl; i++)
	{
		r = rand() % vectorOfPersons.size();
		vectorOfPersons.insert(vectorOfPersons.begin() + r, new Vegan);
		_vegans++;
	}

	for (int i = 0; i<zl; i++)
	{
		int r = rand() % 10 + 1;
		if (r <= 8)  vectorOfInfectedPersons.push_back(new CommonDisease);
		if (r == 9)  vectorOfInfectedPersons.push_back(new UltraVegan);
		if (r == 10)  vectorOfInfectedPersons.push_back(new Mutagen);
	}
}

string Country::description()
{
	return "VectorofPersons: " + to_string(persons()) + "  VectorofInfectedPersons: " + to_string(infectedPersons()) + "\n"
		+ "Scientists: " + to_string(_scientists) + "  Vegans: " + to_string(_vegans) + "  Commons: " + to_string(_commons) + "\n"
		+ "Cure progress (0 means ready): " + to_string(_cure) + "\n";
}

string Country::showEveryone()
{
	string text = "";
	text += "PERSONS \n";
	std::vector<Person *>::iterator it = vectorOfPersons.begin();
	while (it != vectorOfPersons.end())
	{
		text += (*it)->description();
		it++;
	}
	text += "\n INFECTED PERSONS \n";
	std::vector<Disease *>::iterator ite = vectorOfInfectedPersons.begin();
	while (ite != vectorOfInfectedPersons.end())
	{
		text += (*ite)->description();
		ite++;
	}
	return text;
}

void Country::fight(fstream &output, int outputInfo)
{
	
	std::vector<Person *>::iterator personOpponent = vectorOfPersons.begin() + rand() % vectorOfPersons.size();
	std::vector<Disease *>::iterator diseaseOpponent = vectorOfInfectedPersons.begin() + rand() % vectorOfInfectedPersons.size();
	int PersonAttack = (*personOpponent)->attack() + _PersonPower;
	int PersonDodge = (*personOpponent)->dodgeChance() + _PersonImmuneSystem;
	if (outputInfo) output << "Fight between \n" << (*personOpponent)->description() << "and \n" << (*diseaseOpponent)->description();
	while (1)
	{
		if (rand() % 2 == 0)
		{
			if ((*diseaseOpponent)->tryAttack() && rand() % 100 + 1 <= PersonDodge)
			{
				InfectPerson(personOpponent);
				output << "Disease won in first move \n"; if (outputInfo) output << "\n";
				break;
			}
		}
		if (rand() % 100 + 1 <= (*personOpponent)->attackChance() && !((*personOpponent)->isDead()))
		{
			(*diseaseOpponent)->damage(PersonAttack);
			if ((*diseaseOpponent)->isDead())
			{
				vectorOfInfectedPersons.erase(diseaseOpponent);
				if ((*diseaseOpponent)->who() == 1)
				{
					output << "ULTRA VEGAN!!! \n";
					std::vector<Person *>::iterator it = personOpponent;
					it -= 2; int kills = rand() % 4 + 2;
					while (it>vectorOfPersons.begin() && it<vectorOfPersons.end() && kills)
					{
						InfectPerson(it);
						it++; kills--;
					}
				}
				output << "Person won \n"; if (outputInfo) output << "\n";
				break;
			}
		}
		if (!((*diseaseOpponent)->isDead()) && (*diseaseOpponent)->tryAttack() && rand() % 100 + 1>PersonDodge)
		{
			InfectPerson(personOpponent);
			output << "Disease won \n"; if (outputInfo) output << "\n";
			break;
		}
	}
}

void Country::spreadVirus(int i, fstream &output)
{
	int days = _LackOfHygiene + 4;
	if (i % (days) == 0)
	{
		std::vector<Person *>::iterator ite = vectorOfPersons.begin() + rand() % vectorOfPersons.size();
		InfectPerson(ite);
		output << "One random person got infected \n";
	}
}

bool Country::searchForCure(fstream &output)
{
	std::vector<int> scientistVector;
	scientistVector.clear();
	std::vector<Person *>::iterator it = vectorOfPersons.begin();
	while (it != vectorOfPersons.end())
	{
		if ((*it)->who() == 1) scientistVector.push_back((*it)->intelligence());
		it++;
	}
	unsigned int i = 0;
	do
	{
		if (scientistVector.size() != 0 && _cure>0 && rand() % 5 == 0)//25% szans ze zrobiono postep
			_cure -= scientistVector[rand() % scientistVector.size()];
		if (_cure<0) _cure = 0;
		i++;
	} while (i<(scientistVector.size() / 10));
	output << "Cure progress: " << to_string(_cure) << "\n";
	if (_cure>0) return false;
	else return true;
}

void Country::cureSomeInfectedPersons(fstream &output)
{
	int r = rand() % 5 + 5;
	for (int i = 0; i<r; i++)//leczenie zarazonych osob, min 5 naraz (obszarowo rozpylany lek)
	{
		if (vectorOfInfectedPersons.size())
		{
			std::vector<Disease *>::iterator ite = vectorOfInfectedPersons.begin() + rand() % vectorOfInfectedPersons.size();
			delete *ite;
			vectorOfInfectedPersons.erase(ite);
			vectorOfPersons.push_back(new CommonPerson);
		}
	}
	output << to_string(r) << " Infected Persons cured \n";
}