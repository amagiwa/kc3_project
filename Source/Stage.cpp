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
	playerState = 0;
	playerSpeed = 4.0f;

	for (int i = 0; i < 100; ++i) {
		shot[i] = new Shot(Vec2{ 0,0 });
		array << shot[i];
	}
	for (int i = 0; i < 3; ++i) {
		bullet[i] = new Bullet(Vec2{ 0,0 });
		array << bullet[i];
	}
	manager = new Manager(size, position);
	interval = 0;
	timing = 0;
}

Stage::~Stage() {
	delete player;
}

void Stage::shotLaunch() {
	if (KeyZ.pressed()) {
		++interval;
		if (interval % 3 == 0) {
			for (int i = 0; i <100; ++i) {
				if (!shot[i]->getIsActive()) {
					shot[i]->setIsActive(true);
					shot[i]->setPosition(player->getPosition());
					//Print << U"a";
					break;
				}
			}
		}
	}
	else {
		interval = 0;
	}

	for (int i = 0; i < 100; ++i) {
		if (shot[i]->getIsActive()) {
			shot[i]->getTexture().draw(Palette::Red);
			if (shot[i]->getPosition().y < 0) {
				shot[i]->setIsActive(false);
			}
		}
	}
}

void Stage::shotCollision() {
	for (int i = 0; i < /*(sizeof * shot) / (sizeof Shot)*/100; ++i) {
		if ((shot[i]->getPosition().x - enemy->getPosition().x) *
			(shot[i]->getPosition().x - enemy->getPosition().x) +
			(shot[i]->getPosition().y - enemy->getPosition().y) *
			(shot[i]->getPosition().y - enemy->getPosition().y)
			< (shot[0]->getSize().y + enemy->getSize().x)*
			(shot[0]->getSize().y + enemy->getSize().x)) {
			shot[i]->setIsActive(false);
		}
	}
}

void Stage::moveBullet() {
	for (int i = 0; i < 3; ++i) {
		bullet[i]->update();
	}
	for (int i = 0; i < 3; ++i) {
		if (bullet[i]->getIsActive()) {
			if ((bullet[i]->getPosition().x - player->getPosition().x) *
				(bullet[i]->getPosition().x - player->getPosition().x) +
				(bullet[i]->getPosition().y - player->getPosition().y) *
				(bullet[i]->getPosition().y - player->getPosition().y)
				< (bullet[0]->getSize().y + player->getSize().x) *
				(bullet[0]->getSize().y + player->getSize().x)) {
				bullet[i]->Object::getTexture().drawAt(bullet[i]->getPosition());
				bullet[i]->setVelocity(Vec2{ 0,0 });
			}
			else {
				bullet[i]->getTexture().draw(Palette::Orange);
			}
		}
	}
}

void Stage::bulletLaunch() {
	for (int i = 0; i < 3; ++i) {
		if (!bullet[i]->getIsActive()) {
			double y = player->getPosition().y - enemy->getPosition().y;
			double x = player->getPosition().x - enemy->getPosition().x;
			bullet[i]->setPosition(enemy->getPosition());
			bullet[i]->setVelocity(Vec2{
				5 * x / sqrt(x * x + y * y),5 * y / sqrt(x * x + y * y) });
			bullet[i]->setIsActive(true);
			//Print << U"a";
			break;
		}
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
	if (++timing > 300) {
		bulletLaunch();
		timing = 0;
	}
	moveBullet();
	shotLaunch();
	shotCollision();

	flame.draw(Palette::Navy);
}
