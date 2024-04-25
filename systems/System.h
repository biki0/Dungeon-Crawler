#pragma once

#include "SFML/Graphics.hpp"

class System {

	public:
		virtual void Update(float dt) {};

		virtual ~System() = default;



};