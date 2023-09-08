#include"Character.h"
using namespace stg;

Character::Character() {
	isAlive = true;
	size = { 32,32 };
	texture = RectF{ Arg::center(position), size };
}

void Character::update() {
	Object::update();
	texture = RectF{ Arg::center(position), size };
}

void Character::render() {
	texture.draw(color);
}
