#pragma once
#include <vector>
#include <stdexcept>
#include <SFML/Graphics/Rect.hpp>
class Animation
{
public:
	int currentFrame{ 0 };
	float frameTimeElapsed{ 0.f };
	float frameDelay{ 0.f };
	bool playing{ true };
	bool waitsToBegin{ false };
	bool currentlyWaitingToStart{ false };
	float startDelay{ 0.f };
	float startWaitTimeElapsed{ 0.f };
	bool looping{ true };
	std::vector<sf::IntRect> frames{};
	Animation() = default;
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
};