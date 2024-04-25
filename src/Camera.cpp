#include "../include/Camera.h"


Camera::Camera() {

	view = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

}

Camera::~Camera() {

}

void Camera::zoom(float zoom_delta) {

    view.zoom(zoom_delta);

}

void Camera::update() {
   
    sf::Vector2f player_position = EntityManager::GetInstance().GetEntity("player")->GetComponent<TransformComponent>()->position;
    view.setCenter(player_position);


}


void Camera::render(sf::RenderWindow& window) {

    window.setView(view);

}