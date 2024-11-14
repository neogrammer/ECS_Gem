#include <ECS/Entity.h>

Entity::Entity()
    : components{ nullptr, nullptr, nullptr, nullptr }
{
    id = numEntities++;
}
int Entity::getID()
{
    return id;
}

int Entity::numEntities = { 0 };