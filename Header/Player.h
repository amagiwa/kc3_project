#pragma once
//#include"Object.h"
#include"Character.h"

namespace stg {
	class Player :public Character {
	private:
	public:
		Player() = default;
		Player(Vec2);
		~Player();
		//void update();
		//void render();
	};
}
