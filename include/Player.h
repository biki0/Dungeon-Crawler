#pragma once

#include <iostream>
#include <vector>
#include <math.h>

#include "EntityManager.h"



class Player {
	
	public:
	
		Player();
		~Player();


		void process_movement();

		void update(float dt);
		void render(sf::RenderWindow& window);


		sf::Vector2f mouse_position;

	private:

		void cast_fireball();



		sf::Clock clock;


		std::shared_ptr<Entity> m_player;
		std::shared_ptr<TransformComponent> transform;
		std::shared_ptr<RigidBodyComponent> rigidbody;
		std::shared_ptr<SpriteComponent> sprite_comp;


		float m_dt;
		float jump_force = 0.98f;



};