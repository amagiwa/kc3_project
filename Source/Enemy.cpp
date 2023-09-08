#include"Enemy.h"
using namespace stg;

Enemy::Enemy(Vec2 pos) {
	//size = Vec2{ 24,72 };
	position = pos;
	//texture = Texture{ U"../enemy.png" };
	hitBody = new HitBody(8);
	color = Palette::Red;
}

Enemy::~Enemy() {
	delete hitBody;
}
