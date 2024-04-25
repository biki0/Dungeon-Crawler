#pragma once
#pragma once

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"
#include "SpriteComponent.h"

class CoinComponent : public Component {

	public:

		CoinComponent(std::shared_ptr<SpriteComponent> sprite_component);
		~CoinComponent();

		void Update() override;


		std::shared_ptr<SpriteComponent> sprite;


};