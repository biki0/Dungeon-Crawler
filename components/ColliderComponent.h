#pragma once

#include <memory>

#include "SFML/Graphics.hpp"

#include "IComponent.h"
#include "SpriteComponent.h"

class ColliderComponent : public Component {

	public:

		ColliderComponent(sf::Sprite& s);
		~ColliderComponent();

		bool CheckCollision(sf::Sprite& s);


		sf::Sprite& sc;

};