#include"Stage.h"
using namespace stg;

Stage::Stage(Vec2 s, Vec2 pos) {
	size = s;
	position = pos;
	areaInfo = {
		(float)position.y,
		(float)(position.y + size.y),
		(float)(position.x + size.x),
		(float)position.x,
		Vec2{position.x + size.x / 2,position.y + size.y / 2}
	};
	flame = Polygon(
		{
			Vec2{0,0},
			Vec2{Scene::Size().x,0},
			Vec2{Scene::Size().x,Scene::Size().y},
			Vec2{0,Scene::Size().y}
		},
		{ {
			position,
			Vec2{position.x,position.y + size.y},
			position + size,
			Vec2{position.x + size.x,position.y}
		} }
	);
	player = new Player(areaInfo.center);
	player->setIsActive(true);
	array << player;
	enemy = new Enemy(Vec2{ areaInfo.center.x,areaInfo.center.y - 100 });
	enemy->setIsActive(true);
	array << enemy;

	for (auto i : step(sizeof shot / sizeof shot[0])) {
		shot[i] = new Shot(Vec2{ 0,0 });
		array << shot[i];
	}
	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		bullet[i] = new Bullet(Vec2{ 0,0 });
		array << bullet[i];
	}
	manager = new Manager(size, position);

	timing = 0;
	timingRadical = 0;
	interval = 0;
	playerDamage = 0;
	enemyDamage = 0;
}

Stage::~Stage() {
	for (auto i : step(array.size())) {
		delete array[i];
	}
}

void Stage::update() {
	manager->moveUser(player);
	manager->update(array);
	manager->solvePosition(player);
	manager->render(array);

	for (auto i : step(array.size())) {
		manager->collectObject(array[i]);
	}

	if (++timing > 100) {
		for (auto i: step(sizeof bullet/sizeof bullet[0])) {
			if (manager->shootBullet(bullet[i], enemy, player))break;
		}
		timing = 0;
	}

	if (++timingRadical > 50) {
		manager->shootBulletRadical(bullet, sizeof bullet / sizeof bullet[0], enemy);
		timingRadical = 0;
	}

	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		if (manager->collideBulletVsObject(bullet[i], player)) {
			++playerDamage;
		}
	}

	for (auto i : step(sizeof shot / sizeof shot[0])) {
		if (manager->collideShotVsObject(shot[i], enemy)) {
			++enemyDamage;
		}
	}

	if (KeyZ.pressed()) {
		if (++interval % 3 == 0){
			manager->shootShot(player, shot);
		}
	}
	else {
		interval = 0;
	}

	flame.draw(Palette::Navy);
	disp(U"被弾回数\nPlayer: ",playerDamage)
		.draw(areaInfo.right + 30, areaInfo.center.y - 30);
	disp(U"Enemy: ", enemyDamage)
		.draw(areaInfo.right + 30, areaInfo.center.y + 50);
	//Print << U"a";
}

Vec2 Stage::getPlayerPosition() {
	return player->getPosition();
}

Vec2 Stage::getEnemyPosition() {
	return enemy->getPosition();
}

Vec2 Stage::getNearestBulletPosition() {
	float min = 10000.0f;
	const Vec2 pPos = player->getPosition();
	Vec2 nPos = pPos;
	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		if (bullet[i]->getIsActive()) {
			if (min > manager->lengthVector(
				bullet[i]->getPosition() - pPos)) {
				min = manager->lengthVector(
				bullet[i]->getPosition() - pPos);
				nPos = bullet[i]->getPosition();
			}
		}
	}
	return nPos;
}

Vec2 Stage::getNearestBulletVelocity() {
	float min = 10000.0f;
	const Vec2 pPos = player->getPosition();
	Vec2 nVel = pPos;
	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		if (bullet[i]->getIsActive()) {
			if (min > manager->lengthVector(
				bullet[i]->getPosition() - pPos)) {
				min = manager->lengthVector(
				bullet[i]->getPosition() - pPos);
				nVel = bullet[i]->getVelocity();
			}
		}
	}
	return nVel;
}

void Stage::movePlayer(int hor, int ver, bool isShift) {
	manager->movePlayer(player, hor, ver, isShift);
}

void Stage::shootShot() {
	static int count = 0;
	if (++count % 3 == 0) {
		count = 0;
		manager->shootShot(player, shot);
	}
}

void Stage::moveEnemyRandom() {
	static Vec2 pos = Vec2{
		Random(areaInfo.left + 50,areaInfo.right - 50),
		Random(areaInfo.upper + 50,areaInfo.lower - 50)
	};
	if (manager->moveToTarget(enemy, pos)) {
		pos = Vec2{
			Random(areaInfo.left + 50,areaInfo.right - 50),
			Random(areaInfo.upper + 50,areaInfo.lower - 50)
		};
	}
}

//
//Array<Vec2> Stage::getBulletsPosition() {
//	Array<Vec2> ary;
//	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
//		if (bullet[i]->getIsActive()) {
//			ary << bullet[i]->getPosition();
//		}
//	}
//	return ary;
//}
//
//Array<Vec2> Stage::getBulletsVelocity() {
//	Array<Vec2> ary;
//	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
//		if (bullet[i]->getIsActive()) {
//			ary << bullet[i]->getVelocity();
//		}
//	}
//	return ary;
//}
//
