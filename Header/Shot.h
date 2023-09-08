#pragma once
#include"Object.h"

namespace stg {
	class Shot :public Object {
	private:
		Triangle texture;
	public:
		Shot() = default;
		Shot(Vec2);
		~Shot();
		void update();
		void render();
		inline Triangle getTexture() const {
			return texture;
		}
	};
}
