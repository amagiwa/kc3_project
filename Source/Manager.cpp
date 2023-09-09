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

float Manager::lengthVector(Vec2 vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void Manager::normalizeVector(Vec2* vec) {
	//float abs = sqrt(vec->x * vec->x + vec->y * vec->y);
	float abs = lengthVector(*vec);
	*vec /= abs;
}

void Manager::initializeObject(Object* object, Vec2 pos) {
	object->setIsActive(true);
	object->setPosition(pos);
	//Print << U"a";
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

bool Manager::checkCollision(HitBody hbl, HitBody hbr) {
	return hbl.getHitBody().intersects(
		hbr.getHitBody());
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
	p->setPosition(p->getPosition() + dPos);
}

void Manager::moveUser(Player* p) {
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

bool Manager::moveToTarget(Object* obj, Vec2 tgt) {
	static int vel = 2;
	Vec2 dist = tgt - obj->getPosition();
	if (lengthVector(dist) < 1) {
		return true;
	}
	normalizeVector(&dist);
	obj->setVelocity(vel * dist);
	return false;
}

void Manager::randomMove(Character* c) {
	// TODO: 実装
	c->setVelocity(Vec2(Random(-5, 5), 1));
}

bool Manager::shootShot(Player* p, Shot* s[]) {
	for (auto i : step(255/*sizeof s / sizeof s[0]*/)) {
		if (!s[i]->getIsActive()) {
			s[i]->setIsActive(true);
			s[i]->setPosition(p->getPosition());
			return true;
		}
	}
	return false;
}

bool Manager::collideShotVsObject(Shot* s, Object* obj) {
	if (checkCollision(s->getHitBody(), obj->getHitBody())) {
		if (s->getIsActive()) {
			//initializeObject(s, Vec2{ 0,0 });
			s->setIsActive(false);
		}
		return true;
	}
	return false;
}

bool Manager::shootBullet(Bullet* bullet, Object* enemy, Object* player) {
	if (!bullet->getIsActive()) {
		initializeObject(bullet, enemy->getPosition());
		float y = player->getPosition().y - enemy->getPosition().y;
		float x = player->getPosition().x - enemy->getPosition().x;
		bullet->setVelocity(Vec2{
						2 * x / sqrt(x * x + y * y),2 * y / sqrt(x * x + y * y) });
		//Print << U"a";
		return true;
	}
	return false;
}

void Manager::shootBulletRadical(Bullet* bullet[], int bulletNum, Object* object) {
	int count = 0;
	float rand = Random(0.0, 1.0) * Math::Pi / 4;
	for (int i = 0; i < bulletNum; ++i) {
		if (!bullet[i]->getIsActive()) {
			initializeObject(bullet[i], object->getPosition());
			bullet[i]->setVelocity(Vec2{
				cos(count * (Math::Pi / 4) + rand),sin((count * (Math::Pi / 4) + rand)) });
			count++;
			if (count >= 8)break;
		}

	}
}

bool Manager::collideBulletVsObject(Bullet* bul, Object* obj) {
	if (bul->getIsActive()) {
		if (checkCollision(bul->getHitBody(), obj->getHitBody())) {
			//bul->Object::getTexture().drawAt(bul->getPosition());
			bul->setVelocity(Vec2{ 0,0 });
			bul->setIsActive(false);
			return true;
		}
	}
	return false;
}

//使わない
void Manager::objectDraw(Array<Object*> objects) {
	for (auto i : step(objects.size())) {
		if (objects[i]->getIsActive()) {
			objects[i]->getTexture().draw(objects[i]->getColor());

		}
	}
}
//使わない
bool Manager::objectCollision(Object* object1, Object* object2) {
	return (object1->getPosition().x - object2->getPosition().x) *
		(object1->getPosition().x - object2->getPosition().x) +
		(object1->getPosition().y - object2->getPosition().y) *
		(object1->getPosition().y - object2->getPosition().y)
		< (object1->getSize().y + object2->getSize().x) *
		(object1->getSize().y + object2->getSize().x);
}
//使わない
bool Manager::shotLaunch(Shot* shot, Object* object) {
	if (!shot->getIsActive()) {
		//Print << U"a";
		initializeObject(shot, object->getPosition());
		return true;
	}
	return false;
}
