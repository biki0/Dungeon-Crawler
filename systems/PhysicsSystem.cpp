#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem() {

}

PhysicsSystem::~PhysicsSystem() {

}

void PhysicsSystem::Update(float dt) {

	auto& entities = EntityManager::GetInstance().entities;
	auto& entitiesEnemy = EntityManager::GetInstance().enemies;

	for (auto it = entitiesEnemy.begin(); it != entitiesEnemy.end(); ++it) {
		
		for (auto& entity : it->second) {
			
			auto tc = entity->GetComponent<TransformComponent>();
			auto rb = entity->GetComponent<RigidBodyComponent>();

			if (tc && rb) {

				//rb->ApplyForce(0.0f, rb->gravity);

				rb->velocity.x += rb->acceleration.x;
				rb->velocity.y += rb->acceleration.y;

				rb->velocity.x *= rb->damping;
				rb->velocity.y *= rb->damping;

				tc->position.x += rb->velocity.x * dt;
				tc->position.y += rb->velocity.y * dt;

				rb->acceleration.x = 0.0f;
				rb->acceleration.y = 0.0f;

			}
		}

	}

	for (auto it = entities.begin(); it != entities.end(); ++it) {

		auto entity = it->second;

		auto tc = entity->GetComponent<TransformComponent>();
		auto rb = entity->GetComponent<RigidBodyComponent>();

		if (tc && rb) {

			rb->velocity.x += rb->acceleration.x;
			rb->velocity.y += rb->acceleration.y;

			rb->velocity.x *= rb->damping;
			rb->velocity.y *= rb->damping;

			tc->position.x += rb->velocity.x * dt;
			tc->position.y += rb->velocity.y * dt;

			rb->acceleration.x = 0.0f;
			rb->acceleration.y = 0.0f;

		}

	}

	

}














