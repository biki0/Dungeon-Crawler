#include "CoinComponent.h"

CoinComponent::CoinComponent(std::shared_ptr<SpriteComponent> sprite_component) {
	sprite = sprite_component;
}

CoinComponent::~CoinComponent() {

}


void CoinComponent::Update() {

	//for (int i = 0; i < 4; ++i) {
		sprite->PlayFrame(0, 0*16, 100, 4);
		std::cout << "COINNN" << std::endl;
	//}


}





