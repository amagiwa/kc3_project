#include"Player.h"
using namespace stg;

Player::Player(Vec2 pos) :Character() {
	position = pos;
	/*
	texture[0] = Texture{ U"../straight.png" };
	texture[1] = Texture{ U"../left.png" };
	texture[2] = Texture{ U"../right.png" };
	*/
	hitBody = new HitBody(8);
	color = Palette::Blue;
}

Player::~Player() {
	delete hitBody;
}
