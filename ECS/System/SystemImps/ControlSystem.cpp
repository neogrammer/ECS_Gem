#include <ECS/System/Systems.h>


void ControlSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_)
{
    auto filteredEntities = filterEntities<PlayerControllerComponent>(entities_);

    // Update positions based on velocities and deltaTime
    for (auto& entity : filteredEntities) 
    {
        entity->get<PlayerControllerComponent>()->Update(deltaTime);
    }
}