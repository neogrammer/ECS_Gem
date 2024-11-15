#include <ECS/Component/Components.h>

ActionMap<int> PlayerControllerComponent::map = {};

PlayerControllerComponent::PlayerControllerComponent()
	: ActionTarget<int>{map}
{
	

	// realtime events
	// Keyboard pressed commands
	map.map(PlayerInputs::X, Action(sf::Keyboard::Space));
	map.map(PlayerInputs::Y, Action(sf::Keyboard::X));
	map.map(PlayerInputs::A, Action(sf::Keyboard::Num0));
	map.map(PlayerInputs::B, Action(sf::Keyboard::Space));
	map.map(PlayerInputs::L1, Action(sf::Keyboard::Num7));
	map.map(PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	map .map(PlayerInputs::Start, Action(sf::Keyboard::Enter));
	map .map(PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction controls
	map.map(PlayerInputs::Up, Action(sf::Keyboard::Up));
	map.map(PlayerInputs::Down, Action(sf::Keyboard::Down));
	map.map(PlayerInputs::Left, Action(sf::Keyboard::Left));
	map.map(PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Controls
	// Axis mappings
	map.map(PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	map.map(PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	map.map(PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	map.map(PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mappings
	map.map(PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	map.map(PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

	setupBindings();

}

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::setupBindings()
{
	bind(PlayerInputs::DPadX, [this](const sf::Event& e) {
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > 50.f)
		{
			rightPressed = true;
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < -50.f)
		{
			leftPressed = true;
		}


		});

	bind(PlayerInputs::AxisX, [this](const sf::Event& e) {

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 50.f)
		{
			rightPressed = true;
		}
		else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -50.f)
		{
			leftPressed = true;
		}

		});

	bind(PlayerInputs::Right, [this](const sf::Event& e) {
		rightPressed = true;
		});
	bind(PlayerInputs::Left, [this](const sf::Event& e) {
			leftPressed = true;
		});
	bind(PlayerInputs::Up, [this](const sf::Event& e) {
		upPressed = true;
		});
	bind(PlayerInputs::Down, [this](const sf::Event& e) {
		downPressed = true;
		});


	bind(PlayerInputs::JoyX, [this](const sf::Event& e) {
		attackPressed = true;
		});

	bind(PlayerInputs::X, [this](const sf::Event& e) {
		attackPressed = true;
		});
}

void PlayerControllerComponent::Update(float dt_)
{
	attackPressed = false;
	pressedButtons[ButtonID::X] = false;
	upPressed = false;
	pressedButtons[ButtonID::Up] = false;

	downPressed = false;
	pressedButtons[ButtonID::Down] = false;

	leftPressed = false;
	pressedButtons[ButtonID::Left] = false;

	rightPressed = false;
	pressedButtons[ButtonID::Right] = false;


	ActionTarget<int>::processEvents();

	if (attackPressed)
		pressedButtons[ButtonID::X] = true;
	if (upPressed)
		pressedButtons[ButtonID::Up] = true;
	if (downPressed)
		pressedButtons[ButtonID::Down] = true;
	if (leftPressed)
		pressedButtons[ButtonID::Left] = true;
	if (rightPressed)
		pressedButtons[ButtonID::Right] = true;


}
