#pragma once
#include "Person.h"
#include "Disease.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Country //Klasa  zarządzająca przebiegiem zdarzeń w ciągu jednego dnia, posiada ona paramtery determinujące szanse człowieka na wygraną w walce z chorobą
{
	std::vector<Person *> vectorOfPersons; 
	std::vector<Disease *> vectorOfInfectedPersons;
	int _PersonPower, _PersonImmuneSystem, _scienceLevel, _veganLevel, _LackOfHygiene;
	int _scientists, _vegans, _commons;//
	int _cure;
public:
	Country(unsigned int population, int sl, int vl, int zl);//Przeprowadza całą symulację trwania epidemii, zależną od wartości początkowych jej zmiennych.
	int persons(); //Zrwaca rozmiar wektora osób
	int infectedPersons();//Zwraca rozmiar wektora osób zainfekowanych
	int cure();//Zwraca wartość postępu szukania lekarstwa (od 10000 do 0)
	void InfectPerson(std::vector<Person *>::iterator personOpponent);//W przypadku walki wygranej przez chorobę, funcja ta zaraża człowieka chorobą z którą przegrał walkę.
	void fight(fstream &output, int outputInfo);//Symuluje walkę pomiędzy osobą a chorobą. Choroba nie zadaje osobie żadnych obrażeń, w przypadku wygranej po prostu zaraża osobę, natomiast w przypadku przegranej jednostka tej choroby ginie. Jeśli wygrywa osoba, to nie zostaje zarażona. Wynik walki jest uzależniony od parametrów zarówno choroby, jak i osoby, wybieranych losowo, jednak z innym przedziałem losowości w przypadku różnych klas chorób i osób.
	void spreadVirus(int i, fstream &output);//Zaraża losowo wybraną osobę co 4 dni. Czyli symulacja naturalnego rozprzestrzeniania sie wirusa
	bool searchForCure(fstream &output);//Naukowcy szukają lekarstwa. Powodzenie poszukiwań zależne jest od wartości ich inteligencji, a jego wartość jest losowana pod koniec każdego dnia i odejmowana od puli (10000 to początkowa wartość puli)
	void cureSomeInfectedPersons(fstream &output);//Jeśli wartość _cure będzie równa 0 funkcja ta zaczyna leczyć ludzi. Lekarstwo jest losowo rozpraszane na kilka (ilość losowa) jednostek, a każda z nich ma 50% szans na powrót do zdrowia

	string description();//Zwraca ilość osób zdrowych, chorych, postęp szukania lekarstwa itp.  używana do  wyświetlenia wartości początkowych na początku trwania programu
	string showEveryone();//Wypisuje osoby zdrowe oraz zarażone po ich wektorach
};