#pragma once
#include "AI.h"

class Action;

class Actor : public AI
{
protected:
	int ammo = 0;
	int weapon = 1;
	int playerDistance = 5;

public:
	Actor();

	inline int GetAmmo() { return ammo; };
	inline int GetWeapon() { return weapon; };
	inline int GetPlayerDistance() { return playerDistance; };

	inline void SetAmmo(int _ammo) { ammo = _ammo; };
	inline void SetWeapon(int _weapon) { weapon = _weapon; };
	inline void SetPlayerDistance(int _playerDistance) { playerDistance = _playerDistance; };
};

