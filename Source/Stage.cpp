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
}

Stage::~Stage() {
	for (auto i : step(array.size())) {
		delete array[i];
	}
}

void Stage::update() {
	manager->userMove(player);
	manager->update(array);
	manager->solvePosition(player);
	manager->render(array);

	for (auto i : step(array.size())) {
		manager->collectObject(array[i]);
	}

	if (++timing > 100) {
		for (auto i: step(sizeof bullet/sizeof bullet[0])) {
			if (manager->bulletLaunch(bullet[i], enemy, player))break;
		}
		timing = 0;
	}

	if (++timingRadical > 50) {
		manager->bulletLaunchRadical(bullet, sizeof bullet / sizeof bullet[0], enemy);
		timingRadical = 0;
	}

	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		manager->bulletCollision(bullet[i], player);
	}

	if (KeyZ.pressed()) {
		if (++interval % 3 == 0) {
			for (auto i : step(sizeof shot / sizeof shot[0])) {
				if (manager->shotLaunch(shot[i], player))break;
			}
		}
	}
	else {
		interval = 0;
	}

	for (auto i : step(sizeof shot / sizeof shot[0])) {
		manager->shotCollision(shot[i], enemy);
	};

	flame.draw(Palette::Navy);
	Print << U"a";
}

Vec2 Stage::getPlayerPosition() {
	return player->getPosition();
}

Vec2 Stage::getEnemyPosition() {
	return enemy->getPosition();
}

Array<Vec2> Stage::getBulletsPosition() {
	Array<Vec2> ary;
	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		if (bullet[i]->getIsActive()) {
			ary << bullet[i]->getPosition();
		}
	}
	return ary;
}

Array<Vec2> Stage::getBulletsVelocity() {
	Array<Vec2> ary;
	for (auto i : step(sizeof bullet / sizeof bullet[0])) {
		if (bullet[i]->getIsActive()) {
			ary << bullet[i]->getVelocity();
		}
	}
	return ary;
}

void Stage::movePlayer(int hor, int ver, bool isShift) {
	manager->movePlayer(player, hor, ver, isShift);
}
