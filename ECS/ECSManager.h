#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <ECS/Entity/Entities.h>
#include <ECS/Component/Components.h>
#include <ECS/System/Systems.h>


// ECS Manager
class ECSManager {
public:
    sf::RenderWindow& wnd;
    ECSManager(sf::RenderWindow& wnd_); 
    ~ECSManager() = default;
    std::shared_ptr<Entity> AddEntity();
    std::shared_ptr<Entity> getEntity(int id_);
    template <typename ComponentType>
    void AddComponent(std::shared_ptr<Entity>& entity, std::shared_ptr<ComponentType>) {
        entity->addComponent<ComponentType>();
    };
    template <typename ComponentType>
    void AddComponent(int id, std::shared_ptr<ComponentType>) {
        getEntity(id)->addComponent<ComponentType>();
    };
    void AddSystem(System* system); 
    void Update(float deltaTime);
    void Render(float deltaTime);

private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entitiesToAdd;
    std::vector<System*> systems;
};