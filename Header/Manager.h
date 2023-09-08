#pragma once
#include"Object.h"
#include"HitBody.h"
#include"Character.h"

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
		void userMove(Character*);
	};
}
