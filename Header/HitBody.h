#pragma once

namespace stg {
	class HitBody {
	private:
		Vec2 position;
		float size;
		Circle body;
	public:
		HitBody() = default;
		HitBody(float);
		~HitBody() = default;
		void update(Vec2);
		inline Circle getHitBody() {
			return body;
		}
		inline float getSize() const {
			return size;
		}
		inline void setSize(float s) {
			size = s;
		}
		inline Vec2 getPosition() const {
			return position;
		}
		inline void setPosition(Vec2 pos) {
			position = pos;
		}
	};
}
