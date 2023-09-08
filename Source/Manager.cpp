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
	c->setVelocity(Vec2(Random(-5, 5), 1));
}

void Manager::movePlayer(Player* p, int hor, int ver, bool isShift) {
	Vec2 dPos = { 0,0 };
	int vl = 2;
	if (isShift) {
		vl /= 2;
	}
	switch (hor) {
	case 1:
		dPos.x += vl;
		break;
	case -1:
		dPos.x -= vl;
		break;
	default:
		break;
	}
	switch (ver) {
	case 1:
		dPos.y += vl;
		break;
	case -1:
		dPos.y -= vl;
		break;
	default:
		break;
	}
	p->setVelocity(dPos);
}

void Manager::userMove(Player* p) {
	Vec2 dPos = { 0,0 };
	p->setVelocity(dPos);
	int vl = 2;
	//bool isShift = false;
	if (KeyShift.pressed()) {
		//isShift = true;
		vl /= 2;
	}
	if (KeyRight.pressed()) {
		dPos.x += vl;
		//movePlayer(p, 1, 0, isShift);
	}
	else if (KeyLeft.pressed()) {
		dPos.x -= vl;
		//movePlayer(p, -1, 0, isShift);
	}
	if (KeyUp.pressed()) {
		dPos.y -= vl;
		//movePlayer(p, 0, -1, isShift);
	}
	else if (KeyDown.pressed()) {
		dPos.y += vl;
		//movePlayer(p, 0, 1, isShift);
	}
	p->setVelocity(dPos);
}

void Manager::shootShot(Player* p, Shot* s[]) {
	for (auto i : step(sizeof s / sizeof s[0])) {
		if (!s[i]->getIsActive()) {
			s[i]->setIsActive(true);
			s[i]->setPosition(p->getPosition());
		}
	}
}

void Manager::objectInitialize(Object* object, Vec2 pos) {
	object->setIsActive(true);
	object->setPosition(pos);
	//Print << U"a";
}

void Manager::objectDraw(Array<Object*> objects) {
	for (auto i : step(objects.size())) {
		if (objects[i]->getIsActive()) {
			objects[i]->getTexture().draw(objects[i]->getColor());

		}
	}
}

bool Manager::objectCollision(Object* object1, Object* object2) {
	return (object1->getPosition().x - object2->getPosition().x) *
		(object1->getPosition().x - object2->getPosition().x) +
		(object1->getPosition().y - object2->getPosition().y) *
		(object1->getPosition().y - object2->getPosition().y)
		< (object1->getSize().y + object2->getSize().x) *
		(object1->getSize().y + object2->getSize().x);
}

void Manager::objectMoveToTarget(Object* object, Vec2 targetPos) {
	object->setVelocity((object->getPosition() - targetPos) / 10);
}

bool Manager::shotLaunch(Shot* shot, Object* object) {
	if (!shot->getIsActive()) {
		//Print << U"a";
		objectInitialize(shot, object->getPosition());
		return true;
	}
	return false;
}

void Manager::shotCollision(Shot* shot, Object* object) {
	if (objectCollision(shot, object))
	{
		shot->setIsActive(false);
	}
}

bool Manager::bulletLaunch(Bullet* bullet, Object* enemy, Object* player) {
	if (!bullet->getIsActive()) {
		objectInitialize(bullet, enemy->getPosition());
		double y = player->getPosition().y - enemy->getPosition().y;
		double x = player->getPosition().x - enemy->getPosition().x;
		bullet->setVelocity(Vec2{
						2 * x / sqrt(x * x + y * y),2 * y / sqrt(x * x + y * y) });
		//Print << U"a";
		return true;
	}
	return false;
}

void Manager::bulletLaunchRadical(Bullet* bullet[], int bulletNum, Object* object) {
	int count = 0;
	float rand = Random(0.0, 1.0) * Math::Pi / 4;
	for (int i = 0; i < bulletNum; ++i) {
		if (!bullet[i]->getIsActive()) {
			objectInitialize(bullet[i], object->getPosition());
			bullet[i]->setVelocity(Vec2{
				cos(count * (Math::Pi / 4) + rand),sin((count * (Math::Pi / 4) + rand)) });
			count++;
			if (count >= 8)break;
		}

	}
}

void Manager::bulletCollision(Bullet* bullet, Object* object) {
	if (bullet->getIsActive()) {
		if (objectCollision(bullet, object)) {
			bullet->Object::getTexture().drawAt(bullet->getPosition());
			bullet->setVelocity(Vec2{ 0,0 });
			bullet->setIsActive(false);
		}
	}
}
