#pragma once

#include <ECS/Component/Animation.h>
#include <unordered_map>
#include <ECS/Component/ComponentEnums.h>
#include <FSM/Events.h>

namespace lut
{
	extern std::unordered_map<Animation*, AnimID> animIDLUT;

	template<typename Event>
	std::unordered_map<std::string, Event> eventLUT = {
		{"StoppedMoving", EventStoppedMoving{}},
		{"StartedMoving", EventStartedMoving{}},
		{"StartedShooting", EventStartedShooting{}},
		{"StoppedShooting", EventStoppedShooting{}}
	};
}
