#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"
#include "TransformComponent.h"

class RigidBodyComponent : public Component {

	public:

		RigidBodyComponent(std::shared_ptr<TransformComponent> transform, float mass = 1.f, float gravity = 12.8f);

		void ApplyForce(float force_x, float force_y);
		void Update(float dt) override;

		
		std::shared_ptr<TransformComponent> transform;

		sf::Vector2f acceleration;
		sf::Vector2f velocity;

		float mass;
		float gravity;
		float damping = 0.98f;

};