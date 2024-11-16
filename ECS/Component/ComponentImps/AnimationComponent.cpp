#include <ECS/Component/Components.h>
#include <ECS/LUT.h>

Animation* AnimationComponent::backup = nullptr;

Animation& AnimationComponent::get()
{
    return animAtlas[currAnimID];
}
Animation& AnimationComponent::get(AnimID id_)
{
        return animAtlas[id_];
}
Animation& AnimationComponent::getSetAnim()
{
    return animations[currAnimID].animset[(int)currDir];

}
Animation& AnimationComponent::getSetAnim(AnimID id_)
{
    return animations[id_].animset[(int)currDir];
}
void AnimationComponent::setAnimNames(AnimID id_, std::string name_)
{
    for (auto& anim : animations[id_].animset)
    {
        anim.setName(name_);
    }
}

void AnimationComponent::setAnimFrameDelays(AnimID id_, std::array<float, 8> delays_)
{
    for (int i = 0; i < 8; i++)
        animations[id_].animset[i].frameDelay = delays_[i];

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

sf::IntRect& AnimationComponent::getSetFrame(int index)
{
    if (index == -1)
    {
        return animations[currAnimID].animset[(int)currDir].getCurrentFrame();
    }
    else
        return animations[currAnimID].animset[(int)currDir].getFrame(index);
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
    animAtlas[id_].setLooping(true);

    lut::animIDLUT.emplace(&animAtlas[id_], id_);

    if (animAtlas.find(AnimID::Idle) != animAtlas.end() && backup == nullptr)
         backup = &animAtlas[AnimID::Idle];
}

void AnimationComponent::addAnimationSet8(AnimID id_, std::array<int, 8> numFrames_, int x_, int y_, int w_, int h_)
{
    if (animations.find(id_) != animations.end()) throw std::runtime_error("AnimSet " + std::to_string((int)id_) + " already initialized!");

    if (currAnimID == AnimID::None)
        currAnimID = id_;
    animations[id_] = AnimSet{};
    std::string tmp{ "" };
    switch (id_)
    {
    case AnimID::Idle:
        tmp = "IdleState";
        break;
    case AnimID::Run:
        tmp = "RunningState";
        break;
    case AnimID::Attack:
        tmp = "ShootingState";
        break;
    default:
        tmp = "Default";
        break;
    }
    animations[id_].animID = id_;
    animations[id_].type = AnimSetType::Octo;

    numAnimSets++;
    for (int i = 0; i < 8; i++)
    {
        if (numFrames_[i] == 1)
        {
            animations[id_].animset[i].setName(tmp);
            animations[id_].animset[i].setOrientation(Dir(i));
            animations[id_].animset[i].push_back({ { x_, y_+ i  *  h_ }, { w_, h_ } });
        }
        else
        {
            for (int k = 0; k < numFrames_[i]; k++)
            {
                animations[id_].animset[i].push_back({ {x_ + k * w_,y_ + i * h_ },{w_,h_} });
            }

        }
        animations[id_].animset[i].setLooping(true);

    }
    for (int i =0; i < 8; i++)
        lut::animIDLUT.emplace(&animations[id_].animset[i], id_);

    if (animations.find(AnimID::Idle) != animations.end() && backup == nullptr)
        backup = &animations[AnimID::Idle].animset[(int)currDir];
}

void AnimationComponent::setAnimStartWaits(AnimID id_, bool cond_, float waitDelay_)
{
    for (int i = 0; i < 8; i++)
    {
        animations[id_].animset[i].waitsToBegin = cond_;
        if (cond_ == true)
        {
            animations[id_].animset[i].currentlyWaitingToStart = true;
        }
        animations[id_].animset[i].startDelay = waitDelay_;
    }
    
}

void AnimationComponent::setAnimLooping(AnimID id_, bool cond_)
{
    for (int i = 0; i < 8; i++)
    {
        animations[id_].animset[i].setLooping(cond_);
    }
}
