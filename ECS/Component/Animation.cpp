#include <ECS/Component/Animation.h>

void Animation::push_back(sf::IntRect r_) { frames.push_back(r_); }
void Animation::play() { playing = true; }
void Animation::stop() { playing = false; currentFrame = 0; }
void Animation::pause() { playing = false; }

bool Animation::isWaitingToStart() { return currentlyWaitingToStart; }
void Animation::setWaitToStart(bool cond_) { waitsToBegin = cond_; }
void Animation::setStartDelay(float amt_) { startDelay = amt_; }
void Animation::setFrameDelay(float amt_) { frameDelay = amt_; }
void Animation::setLooping(bool cond_) { looping = cond_; }
void Animation::setFrame(int index_) { if (index_ < 0 || index_ >= frames.size()) { return; } currentFrame = index_; }
void Animation::resetFrameTimer() { frameTimeElapsed = 0.f; }
void Animation::resetStartWaitTimer() { startWaitTimeElapsed = 0.f; }
bool Animation::isOnLastFrame() { return currentFrame == frames.size() - 1; }
int Animation::numFrames() { return (int)frames.size(); }
void Animation::addFrame(sf::IntRect fr_) { frames.push_back(fr_); }

void Animation::Update(float dt) {

	if (playing)
	{
		if (currentlyWaitingToStart)
		{
			startWaitTimeElapsed += 1.0f/60.f;

			if (startWaitTimeElapsed >= startDelay)
			{
				startWaitTimeElapsed = 0.f;
				currentlyWaitingToStart = false;
				frameTimeElapsed = 0.f;
				currentFrame = 0;
			}
		}
		else
		{
			// not waiting to begin the animation
			frameTimeElapsed += 1.f/60.f;

			if (frameTimeElapsed > frameDelay)
			{
				frameTimeElapsed = 0.f;

				if (waitsToBegin && looping)
				{
					if (isOnLastFrame())
					{
						currentlyWaitingToStart = true;
					}
				}

				if (!currentlyWaitingToStart)
				{
					if (currentFrame + 1 <= (int)frames.size() - 1)
					{
						currentFrame++;
					}
					else
					{
						if (looping)
						{
							// start over animation
							currentFrame = 0;
							currentlyWaitingToStart = true;
							startWaitTimeElapsed = 0.f;
						}
						else
						{
							// last frame
							currentFrame = (int)frames.size() - 1;
							currentlyWaitingToStart = false;
							startWaitTimeElapsed = 0.f;
						}
					}
				}

			}
		}
	}
}
