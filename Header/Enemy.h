#pragma once
//#include"Object.h"
#include"Character.h"

namespace stg {
	class Enemy :public Character {
	private:
	public:
		Enemy() = default;
		Enemy(Vec2);
		~Enemy();
	};
}
