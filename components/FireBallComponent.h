#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"

class FireBallComponent : public Component {

	public:

		FireBallComponent();
		~FireBallComponent();

		void Update() override;


		int damage;
		int speed;
		float angle;
		bool has_collided;
		sf::Vector2f original_position;
		float max_distance;
		sf::Vector2f direction;

		sf::Clock clock;
		bool clock_started = false;

};
