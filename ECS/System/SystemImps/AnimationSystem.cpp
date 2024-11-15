#include <ECS/System/Systems.h>
#include <ECS/LUT.h>
void AnimationSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) {

    auto filteredEntities = filterEntities<AnimationComponent>(entities_);


    for (auto& e : filteredEntities)
    {
        auto& anim = e->get<AnimationComponent>();

        if (anim->animAtlas[anim->currAnimID].done)
        {
            anim->animAtlas[anim->currAnimID].done = false;
            anim->currAnimID = lut::animIDLUT[anim->backup];
        }
        anim->animAtlas[anim->currAnimID].Update(deltaTime);

    }
}
