#pragma once
#include "AI.h"
#include "world.h"

class Action;

class Actor : public AI
{
protected:
	int ammo = AMMO;
	int weapon = WEAPON;
	int playerDistance = PLAYER_DISTANCE;
	bool money = MONEY;
	bool degree = DEGREE;
	bool lowHealth = LOW_HEALTH;
	int healthPotion = HEALTH_POTION;

public:
	Actor();

	inline int GetAmmo() { return ammo; };
	inline int GetWeapon() { return weapon; };
	inline int GetPlayerDistance() { return playerDistance; };
	inline int GetHealthPotion() { return healthPotion; };

	inline void SetAmmo(int _ammo) { ammo = _ammo; };
	inline void SetWeapon(int _weapon) { weapon = _weapon; };
	inline void SetPlayerDistance(int _playerDistance) { playerDistance = _playerDistance; };
	inline void SetHealthPotion(int n) { healthPotion = n; };
	inline void SetMoney(bool n) { money = n; };
	inline void SetDegree(bool n) { degree = n; };
	inline void SetLowHealth(bool n) { lowHealth = n; };

	inline bool IsLowHealth() { return lowHealth; };
	inline bool HasDegree() { return degree; };
	inline bool HasMoney() { return money; };
};

