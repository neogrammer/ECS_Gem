#include <ECS/Component/Components.h>
#include <FSM/DuckFold.h>

std::string AnimStateMachineComponent::currAnimName()
{
	return fsm.getStateName();
}

void AnimStateMachineComponent::dispatch(auto&& Event)
{
	dispatch(fsm, Event);
}
