#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"

class TransformComponent : public Component {

	public:

		TransformComponent(float x, float y);
		~TransformComponent();


		sf::Vector2f position;
		sf::Vector2f scale;

		sf::Vector2f original_pos;

		float rotation;

};