#pragma once
#include <ECS/Component.h>
#include <SFML/Graphics/Texture.hpp>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <ECS/Component/ComponentEnums.h>
#include <ECS/Component/Animation.h>
#include <ECS/Component/AnimSet.h>

#include <Action/ActionTarget.h>
#include <map>
#include <FSM/PlayerAnimFSM.h>
#include <deque>
#include <FSM/FSMEvent.h>

// Derived Components
class PositionComponent : public Component {
public:
    float x{}, y{};
};

class VelocityComponent : public Component {
public:
    float dx{}, dy{};
};

class RenderableComponent : public Component {
public:
    sf::Texture* tex{ nullptr };
};

class AnimationComponent : public Component
{
public:
    static Animation* backup;
    Dir currDir{ Dir::S };
    std::unordered_map<AnimID, AnimSet> animations;
    std::unordered_map<AnimID, Animation> animAtlas;
    int numAnims{ 0 };
    int numAnimSets{ 0 };

    AnimID currAnimID{ AnimID::None };
    Animation& get();
    Animation& get(AnimID id_);
    Animation& getSetAnim();
    Animation& getSetAnim(AnimID id_);
    void setAnimNames(AnimID id_, std::string name_);
    sf::IntRect& getFrame(int index = -1);
    sf::IntRect& getSetFrame(int index = -1);

    void addAnimation(AnimID id_, int numFrames_, int x_, int y_, int w_, int h_);
    void addAnimationSet8(AnimID id_, std::array<int, 8> numFrames_, int x_, int y_, int w_, int h_);
    void setAnimFrameDelays(AnimID id_, std::array<float, 8> delays_);
    void setAnimStartWaits(AnimID id_, bool cond_ = false, float waitDelay_ = 0.f);
    void setAnimLooping(AnimID id_, bool cond_);
};

class AnimStateMachineComponent : public Component
{
public:
    FSM_Player fsm{};

    std::deque<FSMEvent*> eventsWaiting{};

    std::string currAnimName();
    void dispatch(auto&& Event);

};

class PlayerControllerComponent : public Component, public ActionTarget<int>
{
public:
    bool rightPressed{ false };
    bool leftPressed{ false };
    bool upPressed{ false };
    bool downPressed{ false };
    bool attackPressed{ false };

    static ActionMap<int> map;
    std::map<ButtonID, bool> pressedButtons =
    {
        {ButtonID::Down, false},
        {ButtonID::Up, false},
        {ButtonID::Left, false},
        {ButtonID::Right, false},
        {ButtonID::X, false}
    };
public:
    PlayerControllerComponent();
    ~PlayerControllerComponent();
    void setupBindings();
    void Update(float dt_);
};


using EntTuple = std::tuple<std::shared_ptr<PositionComponent>, std::shared_ptr<RenderableComponent>, std::shared_ptr<VelocityComponent>, std::shared_ptr<AnimationComponent>, std::shared_ptr<PlayerControllerComponent>, std::shared_ptr<AnimStateMachineComponent>>;
