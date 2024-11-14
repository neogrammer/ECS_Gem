#pragma once

#include <vector>
#include <ECS/Entity.h>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

class System {
public:
    virtual void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_);
    virtual void Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime);

    template <typename... ComponentTypes>
    std::vector<std::shared_ptr<Entity>> filterEntities(const std::vector<std::shared_ptr<Entity>>& entities) {
        std::vector<std::shared_ptr<Entity>> filteredEntities;
        for (const auto& entity : entities) {
            if ((entity->hasComponent<ComponentTypes>() && ...)) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    };
};

