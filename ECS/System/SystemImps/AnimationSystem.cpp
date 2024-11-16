#include <ECS/System/Systems.h>
#include <ECS/LUT.h>
void AnimationSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) {

    auto filteredEntities = filterEntities<AnimationComponent>(entities_);

    for (auto& e : filteredEntities)
    {
        auto& comp = e->get<AnimationComponent>();
        auto& anim = comp->animations[comp->currAnimID].animset[(int)comp->currDir];

        if (anim.done)
        {
            anim.done = false;
           comp->currAnimID = lut::animIDLUT[comp->backup];
        }
       anim.Update(deltaTime);

    }

    //for (auto& e : filteredEntities)
    //{
    //    auto& anim = e->get<AnimationComponent>();

    //    if (anim->animAtlas[anim->currAnimID].done)
    //    {
    //        anim->animAtlas[anim->currAnimID].done = false;
    //        anim->currAnimID = lut::animIDLUT[anim->backup];
    //    }
    //    anim->animAtlas[anim->currAnimID].Update(deltaTime);

    //}
}
