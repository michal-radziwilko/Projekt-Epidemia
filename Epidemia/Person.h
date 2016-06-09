#pragma once
#include <cstdlib>
#include <string>

using namespace std;

class Person /** *Klasa osób. Posiada wartości ID, HP oraz kilka przydatnych metod. */
{
	static int _personCounter;
	int _personID, _personHP;
public:
	Person() :_personID(_personCounter++), _personHP(100) {}
	int personID() { return _personID; }/** *Zwraca ID osoby. */
	int personHP() { return _personHP; }/** *Zwraca HP osoby. */
	int isDead() { return _personHP>0 ? false : true; }/** *Sprawdza, czy osoba jest martwa. */
	void damage(int dmg) { _personHP -= dmg; }/** *Zadaje dmg osobom. */
	virtual int attack() = 0;/** *Atak wyprowadzany przez osobę */
	virtual int attackChance() = 0;/** *Szansa na atak */
	virtual int dodgeChance() = 0;/** *Szansa na unik */
	virtual int intelligence() = 0;/** *Inteligencja */
	virtual int who() = 0;/** *0-Common 1-Scientist 2-Vegans */

	virtual string description() = 0;
};

class CommonPerson : public Person
{
	int _attack, _attackChance, _dodgeChance;
public:
	CommonPerson() :Person(), _attack(rand() % 10 + 30), _attackChance(rand() % 10 + 50), _dodgeChance(rand() % 10 + 50) {}
	int attack() { return _attack; }
	int attackChance() { return _attackChance; }
	int dodgeChance() { return _dodgeChance; }
	int intelligence() { return 0; }//nigdy sie nie wykona
	virtual int who() { return 0; }

	virtual string description();
}; /** *Klasa przeciętnej osoby. Taka osoba ma mniejsze szanse na wygraną walkę z chorobą. */

class Scientist : public CommonPerson
{
	int _intelligence;
public:
	Scientist() :CommonPerson(), _intelligence(rand() % 100 + 1) {}
	int intelligence() { return _intelligence; }
	virtual int who() { return 1; }

	virtual string description();
};/** *Klasa naukowców. Są oni zupełnie bezbronni, służą tylko znalezieniu lekarstwa oraz jako jedyni posiadają inteligencję. */

class Vegan : public Person
{
	int _attack, _attackChance, _dodgeChance;
public:
	Vegan() :Person(), _attack(rand() % 20 + 70), _attackChance(rand() % 10 + 65), _dodgeChance(rand() % 20 + 80) {}
	int attack() { return _attack; }
	int attackChance() { return _attackChance; }
	int dodgeChance() { return _dodgeChance; }
	int intelligence() { return 0; }//nigdy sie nie wykona
	virtual int who() { return 2; }

	virtual string description();
};/** *Najlepsza klasa w tym programie. Ma duże szanse na wygraną z chorobą. Ogólnie veganie to tacy nowocześni ludzie. A' propos vegan to kiedyś jeszcze w gimbazie był taki Michał co zawsze był przygotowany na lekcje, zawsze miał zadania domowe, dobrze się uczył itp. Pewnego dnia pojechałem na rower i koło Biedronki jak chciałem przejechać na drugą stronę ulicy(jechałem po ścieżce rowerowej przy chodniku) patrzę na prawo- nic nie jedzie, na lewo też no to jadę, a że światło miałem zielone to niczego się nie bałem i później jeszcze przez park jechałem i w końcu do domu. */
