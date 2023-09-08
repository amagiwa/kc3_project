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
		Shot* shot[100];
		Bullet* bullet[100];
		Manager* manager;
		Array<Object*> array;
		int timing;
		int timingRadical;
		int interval;
		Polygon flame;
		struct AreaInfo areaInfo;
	public:
		Stage() = default;
		Stage(Vec2, Vec2);
		~Stage();
		Vec2 getPlayerPosition();
		Vec2 getEnemyPosition();
		Array<Vec2> getBulletsPosition();
		Array<Vec2> getBulletsVelocity();
		void movePlayer(int, int, bool);
		void update();
		inline AreaInfo getAreaInfo() const {
			return areaInfo;
		}
	};
}
