#include"HitBody.h"
using namespace stg;

HitBody::HitBody(float s) {
	position = Vec2{ .0f,.0f };
	size = s;
	body = Circle{ position,size };
}

void HitBody::update(Vec2 pos) {
	position = pos;
}
