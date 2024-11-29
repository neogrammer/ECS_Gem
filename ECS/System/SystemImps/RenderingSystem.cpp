#include <ECS/System/Systems.h>

void  RenderingSystem::Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime)
{
    auto filteredEntities = filterEntities<PositionComponent, RenderableComponent>(entities_);

    //gameView->setCenter({ entities_[0]->get<PositionComponent>()->x, entities_[0]->get<PositionComponent>()->y });

    for (auto& e : filteredEntities)
    {
        if (!e->hasComponent<RenderableComponent>() || !e->hasComponent<PositionComponent>()) { continue; }
        sf::Sprite tmp;
        tmp.setTexture(*e->get<RenderableComponent>()->tex);
        tmp.setPosition({ e->get<PositionComponent>()->x, e->get<PositionComponent>()->y });
        if (e->hasComponent<AnimationComponent>())
        {
            auto& anim = e->get<AnimationComponent>();
            tmp.setTextureRect(anim->getSetFrame());
        }
        wnd_.draw(tmp);
    }

  
}

void RenderingSystem::setView(sf::View& view_)
{
    gameView = &view_;
}
