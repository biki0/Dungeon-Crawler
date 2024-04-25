#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(sf::Sprite& s) : sc(s) {

}

ColliderComponent::~ColliderComponent() {

}

bool ColliderComponent::CheckCollision(sf::Sprite& s) {
    return sc.getGlobalBounds().intersects(s.getGlobalBounds());
}














