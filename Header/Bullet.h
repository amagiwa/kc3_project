#pragma once
#include"Object.h"

namespace stg {
	class Bullet :public Object {
	private:
		Circle texture;
	public:
		Bullet() = default;
		Bullet(Vec2);
		~Bullet();
		void update();
		void render();
		inline Circle getTexture() const {
			return texture;
		}
	};
}
