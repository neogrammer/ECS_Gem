#pragma once

#include <ECS/System.h>
#include <SFML/Graphics/Sprite.hpp>

// Derived Systems
class PhysicsSystem : public System {
public:
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class AnimationSystem : public System {
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class RenderingSystem : public System {
public:
    void Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime) override;
};