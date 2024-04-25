#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "../include/EntityManager.h"
#include "../include/Collision.h"
#include "System.h"

enum class CollisionDirection {
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};
class CollisionSystem : public System {

	public:

		CollisionSystem();
		~CollisionSystem();

		void Update(float dt) override;

		void HandleCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2, float dt);

	private:

		std::vector<std::shared_ptr<Entity>> entities_to_remove;

};