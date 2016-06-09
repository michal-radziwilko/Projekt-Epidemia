#include "Disease.h"
#include "Person.h"
#include "Country.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int Disease::_diseaseCounter = 1;
int Person::_personCounter = 1;

std::vector<int> numbers;
void simulateCountry(int population, int scientists, int vegans, int infected_persons, int outputInfo);
void fileLoad();
fstream output;

int main(int argc, char const *argv[])
{
	int ii = atoi(argv[1]), info = atoi(argv[2]);
	srand(time(NULL));
	fileLoad();
	output.open("output.txt", ios::out | ios::trunc);//Do tego zewnętrznego pliku tekstowego jest zapisywany przebieg symulacji dzień po dniu.
	int index = 0;
	for (int i = 0; i<ii; i++)
	{
		simulateCountry(numbers[index], numbers[index + 1], numbers[index + 2], numbers[index + 3], info);
		index += 4;
	}

}

void simulateCountry(int population, int scientists, int vegans, int infected_persons, int outputInfo)
{
	Country c(population, scientists, vegans, infected_persons);
	cout << c.description();
	output << "NEW COUNTRY NEW SIMULATION \n" << c.description();
	int i = 0;
	while (c.persons()>0 && c.infectedPersons()>0)
	{
		i++;
		c.fight(output, outputInfo);
		if (c.searchForCure(output))
		{
			if (rand() % 2 == 0) c.cureSomeInfectedPersons(output);//50% szans na leczenie
		}
		if (c.persons()) c.spreadVirus(i, output);
	}
	string text = "";
	text = "After " + to_string(i) + " days: \n" + to_string(c.persons()) + " Persons, " + to_string(c.infectedPersons()) + " Infected Persons, "
	 + to_string(population-c.persons()-c.infectedPersons())+ " Dead Persons.\n"	 
	 "Cure progress was: " + to_string(c.cure()) + " (0 means ready) \n"
		+ "------------------------------------------------------------------------------------------------------------ \n\n";
	cout << text;
	output << text;
}

void fileLoad()//Wczytuje dane wejściowe programu z pliku zewnętrznego
{
	fstream file("input.txt", ios::in);
	int n;
	while (file >> n)
	{
		numbers.push_back(n);
	}
}