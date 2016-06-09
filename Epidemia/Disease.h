#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Disease /** *Klasa choroby, posiada parametry takie jak HP i ID choroby oraz cechy choroby od których zależy przebieg walki między nią a człowiekiem. */
{
	static int _diseaseCounter;
	int _diseaseID, _diseaseHP;
public:
	Disease() :_diseaseID(_diseaseCounter++), _diseaseHP(100) {}
	int diseaseID() { return _diseaseID; }
	int diseaseHP() { return _diseaseHP; }
	void damage(int dmg) { _diseaseHP -= dmg; }
	bool isDead() { return _diseaseHP>0 ? false : true; }
	virtual int attackChance() = 0;
	virtual int who() = 0;/** *0-CommonDisease 1-UltraVegan 2-Mutagen */
	virtual bool tryAttack() = 0;

	virtual string description() = 0;
};

class CommonDisease : public Disease
{
	int _attackChance;
public:
	CommonDisease() :Disease(), _attackChance(rand() % 20 + 10) {}
	int attackChance() { return _attackChance; }
	virtual int who() { return 0; }
	virtual bool tryAttack();

	virtual string description();
}; /** *Klasa przeciętnego rodzaju choroby, nie boi się ona vegan */

class UltraVegan : public Disease
{
	int _attackChance;
public:
	UltraVegan() :Disease(), _attackChance(rand() % 4 + 1) {}
	int attackChance() { return _attackChance; }
	virtual int who() { return 1; }
	virtual bool tryAttack();

	virtual string description();
}; /** *Klasa wirusa który spier... ucieka w te pędy, gdy spotka vegana (tak na prawdę to każda osobę którą spotyka) zarażając po drodze kilka innych osób. */

class Mutagen : public Disease
{
	int _attackChance, _attackCount;
public:
	Mutagen() :Disease(), _attackChance(rand() % 20 + 10), _attackCount(rand() % 3 + 1) {}
	int attackChance() { return _attackChance; }
	int attackCount() { return _attackCount; }
	virtual int who() { return 2; }
	virtual bool tryAttack();

	virtual string description();
}; /** *Klasa silnego wirusa, wyprowadza on kilka ataków jednocześnie podczas walki. */
