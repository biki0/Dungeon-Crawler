#include "TransformComponent.h"

TransformComponent::TransformComponent(float x, float y) {

	position.x = x;
	position.y = y;

	scale = { 1.f, 1.f };
	
	original_pos.x = x;
	original_pos.y = y;
	
	rotation = 0.f;

}

TransformComponent::~TransformComponent() {

}
