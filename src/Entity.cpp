#include "../include/Entity.h"


Entity::Entity() {

	is_collidable = false;


	


}

Entity::~Entity() {


}



void Entity::update(float dt) {

	/*auto rb = GetComponent<RigidBodyComponent>();
	if (rb) {
		rb->Update(dt);
	}

	auto s = GetComponent<SpriteComponent>();
	if (s) {
		s->Update();
	}*/


}

void Entity::render(sf::RenderWindow& window) {

	std::shared_ptr<SpriteComponent> sc = GetComponent<SpriteComponent>();
	if (sc) {
		window.draw(sc->sprite);
	}
}
