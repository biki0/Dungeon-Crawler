#include "../include/Player.h"


Player::Player() {

    m_player = EntityManager::GetInstance().CreateEntity("player");
    m_player->is_collidable = true;
    m_player->entity_type = "player";
    transform = m_player->AddComponent<TransformComponent>(32, -300);
    sprite_comp = m_player->AddComponent<SpriteComponent>(transform, "assets/player.png", 32, 32);
    rigidbody = m_player->AddComponent<RigidBodyComponent>(transform);
    //transform->scale = {2, 2};

}

Player::~Player() {

}

void Player::cast_fireball() {

    if (mouse_position.x < transform->position.x) {
        sprite_comp->sprite.setOrigin({ sprite_comp->sprite.getLocalBounds().width, 0 });
        transform->scale = { -1, 1 };
    }
    else {
        sprite_comp->sprite.setOrigin({ 0, 0 });
        transform->scale = { 1, 1 };
    }


    std::cout << "Fireball casted" << std::endl;
    static int fire_ball_count = 0;
    std::string fire_ball_name = "fireball" + std::to_string(fire_ball_count++);

    auto fireball = EntityManager::GetInstance().CreateEntity(fire_ball_name);
    fireball->entity_type = "spell";
    fireball->is_collidable = true;

    auto tc = fireball->AddComponent<TransformComponent>(transform->position.x+16, transform->position.y+16);
    auto sc = fireball->AddComponent<SpriteComponent>(tc, "assets/spells/fireball.png", 64, 64);
    auto fc = fireball->AddComponent<FireBallComponent>();

    fc->angle = std::atan2(mouse_position.y - transform->position.y, mouse_position.x - transform->position.x);
    tc->rotation = (fc->angle * 180 / PI);
    tc->scale = { 0.5, 0.5 };
    sc->sprite.setOrigin(sf::Vector2f(sc->sprite.getLocalBounds().width, sc->sprite.getLocalBounds().height) / 2.f); //took forever...

    fc->direction = { std::cos(fc->angle), std::sin(fc->angle) };
    float length = std::sqrt(fc->direction.x * fc->direction.x + fc->direction.y * fc->direction.y);
    if (length != 0) {
        fc->direction /= length;
    }
   
    fc->clock.restart();

}

void Player::process_movement() {

    sprite_comp->PlayFrame(0, 1 * 32, 200, 2);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rigidbody->ApplyForce(-9.f, 0.f);
        sprite_comp->PlayFrame(0, 3 * 32, 200, 2);


        sprite_comp->sprite.setOrigin({ sprite_comp->sprite.getLocalBounds().width, 0 });
        transform->scale = { -1, 1 };


    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rigidbody->ApplyForce(9.f, 0.f);
        sprite_comp->PlayFrame(0, 3 * 32, 200, 2);

        sprite_comp->sprite.setOrigin({ 0, 0 });
        transform->scale = { 1, 1 };



    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        //rigidbody->ApplyForce(0.f, -68.f * jump_force);
        rigidbody->ApplyForce(0.f, -9.f);
        sprite_comp->PlayFrame(0, 5 * 32, 100, 8);



    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

        //rigidbody->ApplyForce(0.f, 68.f);
        rigidbody->ApplyForce(0.f, 9.f);

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        transform->position = { 127, 300 };
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {

        sprite_comp->PlayFrame(0, 8 * 32, 10, 8);

    }

    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && clock.getElapsedTime().asSeconds() > 0.5) {
        cast_fireball();
        clock.restart();
    }





}



void Player::update(float dt) {

    m_dt = dt;

    this->process_movement();


    
    //std::cout << transform->position.x << ", " << transform->position.y << std::endl;

}

void Player::render(sf::RenderWindow& window) {


  


}





