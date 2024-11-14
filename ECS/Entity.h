#pragma once

#include <ECS/Component/Components.h>
#include <Assert.h>
class Entity {
public:
    Entity();
    int getID();

    template <typename ComponentType>
    std::shared_ptr<ComponentType>& get()
    {
        assert(this->hasComponent<ComponentType>() && "Entity does not have that component type set up");
        return std::get<std::shared_ptr<ComponentType>>(components);
    }

    template <typename cComponent>
    void addComponent() {
        if (!this->hasComponent<cComponent>())
            std::get<std::shared_ptr<cComponent> >(components) = std::make_shared<cComponent>();
    }

    template <typename ComponentType>
    bool hasComponent() const {
        return std::get<std::shared_ptr<ComponentType>>(components) != nullptr;
    }

private:
    int id{};
    static int numEntities;
    EntTuple components{nullptr,nullptr,nullptr, nullptr};
};