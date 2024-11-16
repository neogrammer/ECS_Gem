#include <ECS/System/Systems.h>

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
                    animState->currDir = Dir::N;

                }
                else if (control->pressedButtons[ButtonID::Down])
                {
                    animState->currDir = Dir::S;

                }
                else if (control->pressedButtons[ButtonID::Left])
                {
                    animState->currDir = Dir::W;

                }
                else if (control->pressedButtons[ButtonID::Right])
                {
                    animState->currDir = Dir::E;

                }
            }

        }
        


        position->x += velocity->dx * deltaTime;
        position->y += velocity->dy * deltaTime;

    }


}