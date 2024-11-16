#pragma once
#include <vector>
#include <stdexcept>
#include  <string>
#include <SFML/Graphics/Rect.hpp>
#include <ECS/Component/ComponentEnums.h>
class Animation
{
public:
	int    currentFrame{ 0 };
	float frameTimeElapsed{ 0.f };
	float frameDelay{ 0.f };
	bool playing{ true };
	bool waitsToBegin{ false };
	bool currentlyWaitingToStart{ false };
	float startDelay{ 0.f };
	float startWaitTimeElapsed{ 0.f };
	bool looping{ true };
	bool done{ false };
	std::string name{ "Default" };
	Dir orientation{ Dir::S };
	std::vector<sf::IntRect> frames{};
	Animation();
	Animation(std::string name_, Dir orient_);

	~Animation() = default;
	inline sf::IntRect& getCurrentFrame() noexcept 	{ 	return frames[currentFrame];	}
	inline sf::IntRect& getFrame(int index)
	{
		if (index < 0 || index >= frames.size()) throw std::runtime_error("Index out of range for an animation frame!");
		return frames[index];
	}
	inline std::vector<sf::IntRect>& getFrameVec() noexcept	{		return frames;	}
	void push_back(sf::IntRect r_);
	void play();
	void stop();
	void pause();
	bool isWaitingToStart(); 
	void setWaitToStart(bool cond_);
	void setStartDelay(float amt_); 
	void setFrameDelay(float amt_); 
	void setLooping(bool cond_); 
	void setFrame(int index_); 
	void resetFrameTimer(); 
	void resetStartWaitTimer(); 
	bool isOnLastFrame(); 
	int numFrames(); 
	void addFrame(sf::IntRect fr_); 
	void Update(float dt);
	void setName(std::string name_);
	inline std::string& getName() { return name; }
	inline Dir getOrientation() { return orientation; }
	inline void setOrientation(Dir d_) { orientation = d_; }

};