#include <ECS/System/Systems.h>

void PhysicsSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) {
    // Iterate over entities with Position and Velocity components
    // Update positions based on velocities and deltaTime
    auto filteredEntities = filterEntities<PositionComponent, VelocityComponent>(entities_);

    // Update positions based on velocities and deltaTime
    for (auto& entity : filteredEntities) {
        auto& velocity = entity->get<VelocityComponent>();
        auto& position = entity->get<PositionComponent>();
        position->x += velocity->dx * deltaTime;
        position->y += velocity->dy * deltaTime;
    }


}