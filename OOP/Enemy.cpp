#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{

}
Enemy::Enemy(const int _velocity,
	const char* const _text, const ConsoleColor _fg, const ConsoleColor _bg, short _x, short _y) : BaseObject(_text, _fg, _bg, _x, _y)
{

}
Enemy::Enemy(const Enemy& _obj) : BaseObject(_obj)
{
	velocity = _obj.velocity;
}
Enemy& Enemy::operator=(const Enemy& _obj)
{
	if (this != &_obj)
	{
		velocity = _obj.velocity;
		BaseObject::operator=(_obj);
	}
	return *this;
}
Enemy::~Enemy()
{

}