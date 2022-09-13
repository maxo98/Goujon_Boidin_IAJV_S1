#pragma once
#include "AI.h"
class Actor;

class Effect
{
public:
	void virtual ApplyEffect(AI* actor) = 0;
};

class AttackPlayer: public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class ReloadEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class GetWeaponEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class MoveToPlayerEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class GetMoneyEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class GetDegreeEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class GetHealthPotionEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class GetHealthEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class StealWeaponEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};

class StealPotionEffect : public Effect
{
public:
	void virtual ApplyEffect(AI* actor);
};