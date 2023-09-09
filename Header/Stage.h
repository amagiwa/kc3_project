#pragma once
#include"Player.h"
#include"Enemy.h"
#include"Shot.h"
#include"Bullet.h"
#include"Manager.h"

namespace stg {
	class Stage {
		struct AreaInfo {
			float upper;
			float lower;
			float right;
			float left;
			Vec2 center;
			AreaInfo() = default;
			AreaInfo(float u, float lw, float r, float l, Vec2 c) {
				upper = u;
				lower = lw;
				right = r;
				left = l;
				center = c;
			}
		};
	private:
		Vec2 size;
		Vec2 position;
		Player* player;
		Enemy* enemy;
		Shot* shot[256];
		Bullet* bullet[256];
		Manager* manager;
		Array<Object*> array;
		int timing;
		int timingRadical;
		int interval;
		int playerDamage;
		int enemyDamage;
		const Font disp{ FontMethod::MSDF, 30 };
		Polygon flame;
		struct AreaInfo areaInfo;
	public:
		Stage() = default;
		Stage(Vec2, Vec2);
		~Stage();
		void update();
		Vec2 getPlayerPosition();
		Vec2 getEnemyPosition();
		Vec2 getNearestBulletPosition();
		Vec2 getNearestBulletVelocity();
		void movePlayer(int, int, bool);
		void shootShot();
		void moveEnemyRandom();
		inline AreaInfo getAreaInfo() const {
			return areaInfo;
		}
	};
}
