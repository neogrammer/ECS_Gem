#pragma once

enum class AnimID
{
	Idle,
	Walk,
	Attack,
	Run,
	Count,
	None
};

enum PlayerInputs : int
{
	// Keyboard mappable Keypresses
	Up, Down, Left, Right, A, X, Y, B, Start, Select, R1, L1,

	//// Joystick input, like a ps5 controller, DPad* and Axis* are handled differently than the rest of the joystick
	DPadX, DPadY, AxisX, AxisY,
	JoyA, JoyB, JoyX, JoyY, JoyR1, JoyL1, JoyStart, JoySelect
};

enum class ButtonID : int
{
	Up, Left, Down, Right, X
};

enum class Dir : int
{
	S,SE,E,NE,N,NW,W,SW
};

enum class AnimSetType : int
{
	Single, Duo, Quad, Octo
};