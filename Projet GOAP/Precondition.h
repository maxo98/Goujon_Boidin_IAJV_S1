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
		PlayerInRange,
		HasHealthPotion,
		HasMoney,
		HasDegree,
		IsHealthy
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

class HasHealthPotion : public Precondition
{
public:
	HasHealthPotion() { type = Types::HasHealthPotion; }

	bool virtual IsTrue(AI* actor);
};

class HasMoney : public Precondition
{
public:
	HasMoney() { type = Types::HasMoney; }

	bool virtual IsTrue(AI* actor);
};

class HasDegree : public Precondition
{
public:
	HasDegree() { type = Types::HasDegree; }

	bool virtual IsTrue(AI* actor);
};

class IsHealthy : public Precondition
{
public:
	IsHealthy() { type = Types::IsHealthy; }

	bool virtual IsTrue(AI* actor);
};