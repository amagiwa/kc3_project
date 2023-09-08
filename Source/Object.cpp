#include"Object.h"
using namespace stg;

Object::Object() {
	texture = Texture{ U"" };
	size = Vec2{ .0f,.0f };
	position = Vec2{ .0f, .0f };
	velocity = Vec2{ .0f, .0f };
	acceleration = Vec2{ .0f, .0f };
	degree = .0f;
	isActive = false;
	color = ColorF{ .0f,.0f,.0f,.0f };
}

void Object::update() {
	velocity += acceleration;
	position += velocity;
}

void Object::render() {}
