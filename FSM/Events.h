#pragma once
#include <variant>
struct EventJumped {};
struct EventReachedJumpPeak {};
struct EventStartedFalling {};
struct EventLanded { bool isMoving; };
struct EventStartedShooting {};
struct EventStartedMoving {};
struct EventStoppedMoving {};
struct EventStoppedShooting {};