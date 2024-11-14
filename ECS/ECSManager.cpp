#include <ECS/ECSManager.h>

ECSManager::ECSManager(sf::RenderWindow& wnd_) : wnd{ wnd_ }
{}

std::shared_ptr<Entity> ECSManager::AddEntity() {
    std::shared_ptr<Entity> tmp = std::make_shared<Entity>();
    entitiesToAdd.push_back(tmp);
    return tmp;
}

std::shared_ptr<Entity> ECSManager::getEntity(int id_)
{
    for (auto& e : entities)
    {
        if (e->getID() == id_)
        {
            //found it
            return e;
        }
    }
    return nullptr;
}


void ECSManager::AddSystem(System* system) {
    systems.push_back(system);
}

void ECSManager::Update(float deltaTime) {

    if (!entitiesToAdd.empty())
    {
        for (int i = 0; i < entitiesToAdd.size(); i++)
        {
            entities.push_back(entitiesToAdd[i]);
            entitiesToAdd[i].reset();
            entitiesToAdd[i] = nullptr;
        }
        entitiesToAdd.clear();
        entitiesToAdd.shrink_to_fit();
    }
    for (auto& system : systems) {
        system->Update(deltaTime, entities, wnd);
    }
}

void ECSManager::Render(float deltaTime)
{
    systems[0]->Render(wnd, entities, deltaTime);
}
