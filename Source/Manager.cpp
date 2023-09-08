#include"Manager.h"
using namespace stg;

Manager::Manager(Vec2 size,Vec2 pos){
	stageUpper = pos.y;
	stageLower = pos.y + size.y;
	stageRight = pos.x + size.x;
	stageLeft = pos.x;
}

void Manager::update(Array<Object*> obj) {
	for (auto i : step(obj.size())) {
		if (obj[i]->getIsActive()) {
			obj[i]->update();
		}
	}
}

void Manager::render(Array<Object*> obj) {
	for (auto i : step(obj.size())) {
		if (obj[i]->getIsActive()) {
			obj[i]->render();
		}
	}
}

void Manager::collectObject(Object* obj) {
	Vec2 pos = obj->getPosition();
	/*if (pos.x<0 ||
		pos.y<0 ||
		pos.x>Scene::Size().x ||
		pos.y>Scene::Size().y) {
		obj->setIsActive(false);
	}*/
	if (!InRange((float)pos.x, .0f, (float)Scene::Size().x) ||
		!InRange((float)pos.y, .0f, (float)Scene::Size().y)) {
		obj->setIsActive(false);
	}
}

void Manager::solvePosition(Object* obj) {
	Vec2 pos = obj->getPosition();
	Vec2 size = obj->getSize() / 2;
	float x = Clamp((float)pos.x, stageLeft + (float)size.x, stageRight - (float)size.x);
	float y = Clamp((float)pos.y, stageUpper + (float)size.y, stageLower - (float)size.x);
	obj->setPosition(Vec2{ x,y });
}

bool Manager::checkCollision(HitBody* hbl, HitBody* hbr) {
	return hbl->getHitBody().intersects(
		hbr->getHitBody());
}

void Manager::randomMove(Character* c) {
	// TODO: 実装
}

void Manager::userMove(Character* c) {
	Vec2 dPos = { 0,0 };
	c->setVelocity(dPos);
	int vl = 2;
	if (KeyShift.pressed()) {
		vl /= 2;
	}
	if (KeyRight.pressed()) {
		dPos.x += vl;
	}
	else if (KeyLeft.pressed()) {
		dPos.x -= vl;
	}
	if (KeyUp.pressed()) {
		dPos.y -= vl;
	}
	else if (KeyDown.pressed()) {
		dPos.y += vl;
	}
	c->setVelocity(dPos);
}
