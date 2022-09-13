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

private:
	Types type;
};

class HasAmmo: public Precondition
{
	bool virtual IsTrue(AI* actor);

private:
	Types type = Types::HasAmmo;
};

class HasWeapon: public Precondition
{
	bool virtual IsTrue(AI* actor);

private:
	Types type = Types::HasWeapon;
};

class PlayerInRange: public Precondition
{
	bool virtual IsTrue(AI* actor);

private:
	Types type = Types::PlayerInRange;
};
