#pragma once

#include "SFML/Graphics.hpp"
#include "utils.h"


class Component {

	public:
		
		virtual void Init() {};
		virtual void Update() {};
		virtual void Update(float dt) {};
		virtual void Draw() {};
		virtual ~Component() = default;




};

