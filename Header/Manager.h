#pragma once
#include"Object.h"
#include"Character.h"
#include"Player.h"
#include"Shot.h"
#include"Bullet.h"
#include"Hitbody.h"

namespace stg {
	class Manager {
	private:
		float stageUpper;
		float stageLower;
		float stageRight;
		float stageLeft;
	public:
		Manager() = default;
		Manager(Vec2, Vec2);
		~Manager() = default;
		void update(Array<Object*>);
		void render(Array<Object*>);

		float lengthVector(Vec2);
		void normalizeVector(Vec2*);
		void initializeObject(Object*, Vec2);
		void collectObject(Object*);
		void solvePosition(Object*);
		bool checkCollision(HitBody, HitBody);

		void movePlayer(Player*, int, int, bool);
		void moveUser(Player*);
		bool moveToTarget(Object*, Vec2);
		void randomMove(Character*);

		bool shootShot(Player*, Shot* []);
		bool collideShotVsObject(Shot*, Object*);

		bool shootBullet(Bullet*, Object*, Object*);
		void shootBulletRadical(Bullet* [], int, Object*);
		bool collideBulletVsObject(Bullet*, Object*);

		bool shotLaunch(Shot*, Object*);//使わない
		bool objectCollision(Object*, Object*);//使わない
		void objectDraw(Array<Object*>);//使わない
	};
}
