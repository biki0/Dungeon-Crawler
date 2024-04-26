#include "SkeletonEnemyComponent.h"


SkeletonEnemyComponent::SkeletonEnemyComponent() {

	attack_range = 32.f;
	follow_range = 100.f;
	inplace_range = 110.f;
	
	follow_forever = false;
	is_attackable = true;
	is_attacked = false;

	clock_started = false;

}

SkeletonEnemyComponent::~SkeletonEnemyComponent() {

}















