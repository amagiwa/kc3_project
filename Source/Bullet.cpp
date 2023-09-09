#include"Bullet.h"
using namespace stg;

Bullet::Bullet(Vec2 pos) {
	this->position = pos;
	size = Vec2{ 32,32 };
	texture = Circle{ position, size.x / 2 };
	hitBody = new HitBody(size.x / 4);
	//Object::texture = Texture{ U"../bullet.png" };
	color = Palette::Orange;
}

Bullet::~Bullet() {
	delete hitBody;
}

void Bullet::update() {
	Object::update();
	texture = Circle{ position, size.x / 2 };
	hitBody->update(position);
}

void Bullet::render() {
	texture.draw(color);
}
