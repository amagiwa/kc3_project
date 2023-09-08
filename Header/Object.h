#pragma once
#include"HitBody.h"

namespace stg {
	class Object {
	protected:
		Texture texture;
		HitBody *hitBody;
		bool isActive;
		Vec2 position;
		Vec2 velocity;
		Vec2 acceleration;
		Vec2 size;
		float degree;
		ColorF color;
	public:
		Object();
		virtual ~Object() = default;
		virtual void update();
		virtual void render();
		inline Texture getTexture() const {
			return texture;
		}
		inline HitBody getHitBody() {
			return *hitBody;
		}
		inline bool getIsActive() const {
			return isActive;
		}
		inline void setIsActive(bool isActive) {
			this->isActive = isActive;
		}
		inline Vec2 getPosition() const {
			return position;
		}
		inline void setPosition(Vec2 position) {
			this->position = position;
		}
		inline Vec2 getVelocity() const {
			return velocity;
		}
		inline void setVelocity(Vec2 velocity) {
			this->velocity = velocity;
		}
		inline Vec2 getAcceleration() const {
			return acceleration;
		}
		inline void setAcceleration(Vec2 acceleration) {
			this->acceleration = acceleration;
		}
		inline Vec2 getSize() const {
			return size;
		}
		inline void setSize(Vec2 size) {
			this->size = size;
		}
		inline float getDegree() const {
			return degree;
		}
		inline void setDegree(double degree) {
			this->degree = degree;
		}
		inline ColorF getColor() const{
			return color;
		}
		inline void setColor(ColorF c) {
			color = c;
		}
	};
}
