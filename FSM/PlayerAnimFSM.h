#ifndef PLAYERANIMFSM_H__
#define PLAYERANIMFSM_H__
#include <FSM/DuckFold.h>
#include <optional>
#include <iostream>
#include <type_traits>
#include <variant>

class FSM_Player : public FSM<FSM_Player, PlayerAnimVar>
{
public:
	//std::optional<PlayerAnimVar> On_Event(IdleState& s, const EventJumped& e)	{	return InAirState{}; 	}
	
	/*std::optional<PlayerAnimVar> On_Event(InAirState& s, const EventLanded& e)
	{
		if (e.isMoving)
			return RunningState{};
		else
			return IdleState{};
	}*/
	template <typename State, typename Event>
	std::optional<PlayerAnimVar> On_Event(State&, const Event&) { 	return std::nullopt; 	}
	std::string getStateName()
	{
		if (std::holds_alternative<IdleState>(state_)) { return "IdleState"; }
		else if (std::holds_alternative<ShootingState>(state_)) { return "ShootingState"; }
		else if (std::holds_alternative<InAirState>(state_)) { return "InAirState"; }
		else if (std::holds_alternative<RunningState>(state_)) { return "RunningState"; }
		else if (std::holds_alternative<RunningAndShootingState>(state_)) { return "RunningAndShootingState"; }
		else if (std::holds_alternative<InAirShootingState>(state_)) { return "InAirShootingState"; }
		else if (std::holds_alternative<InAirFallState>(state_)) { return "InAirFallState"; }
		else if (std::holds_alternative<InAirFallShootingState>(state_)) { return "InAirFallShootingState"; }
		else if (std::holds_alternative<InAirPeakShootingState>(state_)) { return "InAirPeakShootingState"; }
		else if (std::holds_alternative<InAirPeakState>(state_)) { return "InAirPeakState"; }
		else { return "NoStateCurrentlyHeld"; }
	}
};

#endif