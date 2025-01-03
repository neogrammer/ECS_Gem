#include <ECS/System/Systems.h>

bool PhysicsSystem::isMovingDiagonal(Entity& owner_)
{
    if (owner_.hasComponent<PlayerControllerComponent>())
    {
        auto& control = owner_.get<PlayerControllerComponent>();

        if (control->movingDiagonal)
        {
            return true;
        }
    }
    return false;
}

void PhysicsSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) {
    // Iterate over entities with Position and Velocity components
    // Update positions based on velocities and deltaTime
    auto filteredEntities = filterEntities<PositionComponent, VelocityComponent>(entities_);
   
    // Update positions based on velocities and deltaTime
    for (auto& entity : filteredEntities) {
        auto& velocity = entity->get<VelocityComponent>();
        auto& position = entity->get<PositionComponent>();
        if (entity->hasComponent<PlayerControllerComponent>())
        {
            auto& control = entity->get<PlayerControllerComponent>();

            if (control->pressedButtons[ButtonID::Up])
            {

                velocity->dy = -300.f;
            }
            else if (control->pressedButtons[ButtonID::Down])
            {
                velocity->dy = 300.f;
            }

            if (!control->pressedButtons[ButtonID::Up] && !control->pressedButtons[ButtonID::Down])
            {
                velocity->dy = 0.f;
            }

            if (control->pressedButtons[ButtonID::Left])
            {
                velocity->dx = -300.f;
            }
            else if (control->pressedButtons[ButtonID::Right])
            {
                velocity->dx = 300.f;
            }

            if (!control->pressedButtons[ButtonID::Left] && !control->pressedButtons[ButtonID::Right])
            {
                velocity->dx = 0.f;

            }
            if (isMovingDiagonal(*entity))
            {
                velocity->dx *= .707f;
                velocity->dy *= .707f;

            }

            if (entity->hasComponent<AnimStateMachineComponent>())
            {
                auto& stateMachine = entity->get<AnimStateMachineComponent>();
                auto name = stateMachine->currAnimName();
                if (control->pressedButtons[ButtonID::Up] || control->pressedButtons[ButtonID::Left] || control->pressedButtons[ButtonID::Right] || control->pressedButtons[ButtonID::Down])
                {
                    if (name != "RunningState")
                    {
                       
                        stateMachine->eventsWaiting.emplace_back(new EventStartedMoving{});

                    }
                   
                }
                
                if (control->pressedButtons[ButtonID::X])
                {
                    if (name != "ShootingState")
                    {

                        stateMachine->eventsWaiting.push_back(new EventStartedShooting{});
                    }
                }

                if (!control->pressedButtons[ButtonID::Up] && !control->pressedButtons[ButtonID::Left] && !control->pressedButtons[ButtonID::Right] && !control->pressedButtons[ButtonID::Down])
                {
                    if (name != "IdleState")
                    {
                        stateMachine->eventsWaiting.push_back(new EventStoppedMoving{});
                    }
                }

                if (!control->pressedButtons[ButtonID::X])
                {
                    if (name == "ShootingState")
                    {
                        if (entity->hasComponent<AnimationComponent>())
                        {
                            auto& animState = entity->get<AnimationComponent>();
                            if (animState->getSetAnim().currentFrame == animState->getSetAnim().numFrames() - 1)
                            {
                                stateMachine->eventsWaiting.push_back(new EventStoppedShooting{});
                            }
                            else
                            {
                                // let the animation playout
                            }
                        }
                    }
                    else if (name == "RunningState")
                    {
                        stateMachine->eventsWaiting.push_back(new EventStoppedShooting{});
                    }
                    else
                    {
                        if (name != "IdleState")
                            stateMachine->eventsWaiting.push_back(new EventStoppedShooting{});

                    }
                }
                

            }


            auto& animState = entity->get<AnimationComponent>();

            if ((control->pressedButtons[ButtonID::Up] && control->pressedButtons[ButtonID::Left]) ||
                (control->pressedButtons[ButtonID::Up] && control->pressedButtons[ButtonID::Right]) ||
                (control->pressedButtons[ButtonID::Down] && control->pressedButtons[ButtonID::Left]) ||
                (control->pressedButtons[ButtonID::Down] && control->pressedButtons[ButtonID::Right]))
            {
                control->movingDiagonal = true;
                
                if (control->pressedButtons[ButtonID::Up] && control->pressedButtons[ButtonID::Left])
                {
                    animState->currDir = Dir::NW;
                }
                else if (control->pressedButtons[ButtonID::Up] && control->pressedButtons[ButtonID::Right])
                {
                    animState->currDir = Dir::NE;

                }
                else if (control->pressedButtons[ButtonID::Down] && control->pressedButtons[ButtonID::Left])
                {
                    animState->currDir = Dir::SW;
                }
                else if (control->pressedButtons[ButtonID::Down] && control->pressedButtons[ButtonID::Right])
                {
                    animState->currDir = Dir::SE;
                }
            }
            else
            {
                if (control->pressedButtons[ButtonID::Up])
                {
                    if (!control->movingDiagonal)
                    {
                        animState->currDir = Dir::N;
                    }
                    else
                    {
                        // wait to let go
                        if (!currentlyLettingGo)
                        {
                            currentlyLettingGo = true;
                            letgoElapsed = 0.f;
                        }
                                                   
                    }

                }
                else if (control->pressedButtons[ButtonID::Down])
                {
                    if (!control->movingDiagonal)
                    {
                        animState->currDir = Dir::S;
                    }
                    else
                    {
                        // wait to let go
                        if (!currentlyLettingGo)
                        {
                            currentlyLettingGo = true;
                            letgoElapsed = 0.f;
                        }
                    }
                }
                else if (control->pressedButtons[ButtonID::Left])
                {
                    if (!control->movingDiagonal)
                    {
                        animState->currDir = Dir::W;
                    }
                    else
                    {
                        // wait to let go
                        if (!currentlyLettingGo)
                        {
                            currentlyLettingGo = true;
                            letgoElapsed = 0.f;
                        }
                    }
                }
                else if (control->pressedButtons[ButtonID::Right])
                {
                    if (!control->movingDiagonal)
                    {
                        animState->currDir = Dir::E;
                    }
                    else
                    {
                        // wait to let go
                        if (!currentlyLettingGo)
                        {
                            currentlyLettingGo = true;
                            letgoElapsed = 0.f;
                        }
                    }
                }

                if (currentlyLettingGo)
                {
                    letgoElapsed += deltaTime;

                    if (letgoElapsed > letgoDelay)
                    {
                        currentlyLettingGo = false;
                        control->movingDiagonal = false;
                    }
                }
            }

            bool found = false;
            for (auto pressed : control->pressedButtons)
            {
                if (pressed.second)
                {
                    found = true;
                }
            }
            if (!found)
            {
                control->movingDiagonal = false;
                // or by time this can happen
            }



        }
        


        position->x += velocity->dx * deltaTime;
        position->y += velocity->dy * deltaTime;

    }


}