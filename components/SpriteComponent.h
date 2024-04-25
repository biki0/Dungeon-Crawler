#pragma once

#include <string>

#include "SFML/Graphics.hpp"

#include "IComponent.h"
#include "TransformComponent.h"

class SpriteComponent : public Component{

	public:	
		
		SpriteComponent(std::shared_ptr<TransformComponent> transform, std::string file_path, int weight, int height);
		SpriteComponent(std::shared_ptr<TransformComponent> transform, sf::Sprite& s);
		~SpriteComponent();

		void PlayFrame(int x, int y, int speed, int total_frame);

		void SetTextureRect(sf::IntRect rect);

		void Update() override;

		std::shared_ptr<TransformComponent> transform;

		sf::Texture texture;
		sf::Sprite sprite;
		sf::IntRect sprite_rect;

		int width;
		int height;
		bool is_renderable;
		bool has_animation = false;
		bool done_ani = false;
	private:

		sf::Clock clock;

};