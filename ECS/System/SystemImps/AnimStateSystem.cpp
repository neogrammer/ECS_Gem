#include <ECS/System/Systems.h>
#include <FSM/Events.h>
#include <ECS/LUT.h>
void AnimStateSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_)
{
    // Update positions based on velocities and deltaTime
    auto filteredEntities = filterEntities<AnimStateMachineComponent, AnimationComponent>(entities_);

    
    

    for (auto& e : filteredEntities)
    {

        auto& stateComp = e->get<AnimStateMachineComponent>();
        auto& animComp = e->get<AnimationComponent>();
        auto nameBefore = stateComp->fsm.getStateName();


        if (!stateComp->eventsWaiting.empty()) {
            for (auto& e : stateComp->eventsWaiting)
            {
                if (e->getName() == "StoppedMoving")
                    dispatch(stateComp->fsm, EventStoppedMoving{});
                else   if (e->getName() == "StartedMoving")
                    dispatch(stateComp->fsm, EventStartedMoving{});
                else   if (e->getName() == "StartedShooting")
                    dispatch(stateComp->fsm, EventStartedShooting{});
                else   if (e->getName() == "StoppedShooting")
                    dispatch(stateComp->fsm, EventStoppedShooting{});
            }
            for (size_t i = stateComp->eventsWaiting.size() - 1; i >= 0 && i < stateComp->eventsWaiting.size(); i--)
            {
                delete stateComp->eventsWaiting[i];
                stateComp->eventsWaiting[i] = nullptr;
                stateComp->eventsWaiting.pop_back();
            }
            stateComp->eventsWaiting.clear();
            stateComp->eventsWaiting.shrink_to_fit();
        }

        auto nameAfter = stateComp->fsm.getStateName();
        if (nameAfter.compare(nameBefore) != 0)
        {
            animComp->animAtlas[animComp->currAnimID].stop();
            // animation changed
            if (nameAfter == "IdleState")
                animComp->currAnimID = AnimID::Idle;
            else if (nameAfter == "ShootingState")
                animComp->currAnimID = AnimID::Attack;
            else if (nameAfter == "RunningState")
                animComp->currAnimID = AnimID::Run;
            animComp->animAtlas[animComp->currAnimID].play();
        }
    }

    
}