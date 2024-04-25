#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(std::shared_ptr<TransformComponent> transform, float mass, float gravity) {

	this->transform = transform;

	acceleration = { 0.f, 0.f };
	velocity = { 0.f, 0.f };
	this->mass = mass;
	this->gravity = gravity;

}

void RigidBodyComponent::ApplyForce(float force_x, float force_y) {

	acceleration.x += force_x / mass;
	acceleration.y += force_y / mass;

}

void RigidBodyComponent::Update(float dt) {

	ApplyForce(0.0f, gravity);

	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	velocity.x *= damping;
	velocity.y *= damping;

	transform->position.x += velocity.x * dt;
	transform->position.y += velocity.y * dt;


	acceleration.x = 0.0f;
	acceleration.y = 0.0f;

}