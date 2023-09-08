#pragma once
#include"Player.h"
#include"Shot.h"
#include"Bullet.h"

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
		void collectObject(Object*);
		void solvePosition(Object*);
		bool checkCollision(HitBody*, HitBody*);
		void randomMove(Character*);
		void movePlayer(Player*, int, int, bool);
		void userMove(Player*);
		void shootShot(Player*, Shot* []);

		void objectInitialize(Object*, Vec2);
		void objectDraw(Array<Object*>);
		bool objectCollision(Object*, Object*);
		void objectMoveToTarget(Object*, Vec2);

		bool shotLaunch(Shot*, Object*);
		void shotCollision(Shot*, Object*);

		bool bulletLaunch(Bullet*, Object*, Object*);
		void bulletLaunchRadical(Bullet* [], int, Object*);
		void bulletCollision(Bullet*, Object*);
	};
}
