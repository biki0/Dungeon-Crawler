#pragma once


#include "SFML/Graphics.hpp"

#include "EntityManager.h"

class Camera {


	public:

		Camera();
		~Camera();

		void zoom(float zoom_delta);
		void update();
		void render(sf::RenderWindow& window);

	
		sf::View view;



};

