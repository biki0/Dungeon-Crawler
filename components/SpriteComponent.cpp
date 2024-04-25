#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::shared_ptr<TransformComponent> transform, std::string file_path, int width, int height) {

	this->transform = transform;

	texture.loadFromFile(file_path);
	
	sprite.setTexture(texture);

	sprite_rect = sf::IntRect(0, 0, width, height);
	sprite.setTextureRect(sprite_rect);
	sprite.setPosition(transform->position);

	this->width = width;
	this->height = height;
	is_renderable = true;

}

SpriteComponent::SpriteComponent(std::shared_ptr<TransformComponent> transform, sf::Sprite& s) {

	this->transform = transform;

	sprite = s;
	sprite.setPosition(transform->position);

	is_renderable = true;

}


SpriteComponent::~SpriteComponent() {

}



void SpriteComponent::PlayFrame(int x, int y, int speed, int total_frame) {
	
		sprite_rect.left = x + width * static_cast<int>((clock.getElapsedTime().asMilliseconds() / speed) % total_frame);
		sprite_rect.top = y;
		sprite_rect.width = width;
		sprite_rect.height = height;

		sprite.setTextureRect(sprite_rect);
		done_ani = true;

}

void SpriteComponent::SetTextureRect(sf::IntRect rect) {
	sprite.setTextureRect(rect);
}

void SpriteComponent::Update() {

	sprite.setPosition(transform->position);
	sprite.setRotation(transform->rotation);
	sprite.setScale(transform->scale);

}







