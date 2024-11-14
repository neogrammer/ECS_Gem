#include <ECS/System/Systems.h>

void AnimationSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) {

    auto filteredEntities = filterEntities<AnimationComponent>(entities_);


    for (auto& e : filteredEntities)
    {
        auto& anim = e->get<AnimationComponent>();

        anim->animAtlas[anim->currAnimID].Update(deltaTime);
    }
}
