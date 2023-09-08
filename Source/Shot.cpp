#include"Shot.h"
using namespace stg;

Shot::Shot(Vec2 pos) {
	size = Vec2{ 16,8 };
	position = pos;
	texture = Triangle{
		Vec2{position.x - size.x / 2, position.y + size.y / 2},
		Vec2{position.x + size.x / 2, position.y + size.y / 2},
		Vec2{position.x, position.y - size.y / 2}
	};
	velocity = Vec2{ 0,-20 };
	hitBody = new HitBody(8);
	color = Palette::Violet;
}

Shot::~Shot() {
	delete hitBody;
}

void Shot::update() {
	Object::update();
	texture = Triangle{
		Vec2{position.x - size.x / 2, position.y + size.y / 2},
		Vec2{position.x + size.x / 2, position.y + size.y / 2},
		Vec2{position.x, position.y - size.y / 2}
	};
}

void Shot::render() {
	texture.draw(color);
}
