#include <ECS\Component\Components.h>


Animation& AnimationComponent::get()
{
    return animAtlas[currAnimID];
}
sf::IntRect& AnimationComponent::getFrame(int index)
{
    if (index == -1)
    {
        return animAtlas[currAnimID].getCurrentFrame();
    }
    else
        return animAtlas[currAnimID].getFrame(index);
}
void AnimationComponent::addAnimation(AnimID id_, int numFrames_, int x_, int y_, int w_, int h_)
{
    if (animAtlas.find(id_) != animAtlas.end()) throw std::runtime_error("Animation " + std::to_string((int)id_) + " already initialized!");

    animAtlas[id_] = Animation{};
    if (currAnimID == AnimID::None)
        currAnimID = id_;
    numAnims++;
    if (numFrames_ == 1)
    {
        animAtlas[id_].push_back({ { x_, y_ }, { w_, h_ } });
    }
    else
    {
        for (int i = 0; i < numFrames_; i++)
        {
            animAtlas[id_].push_back({ {x_ + i * w_,y_},{w_,h_} });
        }

    }
}