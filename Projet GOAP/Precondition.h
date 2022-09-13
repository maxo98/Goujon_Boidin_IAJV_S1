#pragma once

class AI;
class Actor;

class Precondition
{
public:
	enum class Types
	{
		HasAmmo,
		HasWeapon,
		PlayerInRange
	};

	bool virtual IsTrue(AI* actor) = 0;

	inline Types GetType() { return type; };

protected:
	Types type;
};

class HasAmmo: public Precondition
{
public:
	HasAmmo() { type = Types::HasAmmo; }

	bool virtual IsTrue(AI* actor);
};

class HasWeapon: public Precondition
{
public:
	HasWeapon() { type = Types::HasWeapon; }

	bool virtual IsTrue(AI* actor);
};

class PlayerInRange: public Precondition
{
public:
	PlayerInRange() { type = Types::PlayerInRange; }

	bool virtual IsTrue(AI* actor);
};
