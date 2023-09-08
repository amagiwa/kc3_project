#pragma once
#include"Object.h"

namespace stg {
	class Character :public Object {
	protected:
		bool isAlive;
		RectF texture;
	public:
		Character();
		virtual ~Character() = default;
		inline RectF getTexture() const {
			return texture;
		}
		void update();
		void render();
	};
}
