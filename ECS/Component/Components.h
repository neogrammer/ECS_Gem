#pragma once
#include <ECS/Component.h>
#include <SFML/Graphics/Texture.hpp>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <ECS/Component/ComponentEnums.h>
#include <ECS/Component/Animation.h>
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
    std::unordered_map<AnimID, Animation> animAtlas;
    int numAnims{ 0 };
    AnimID currAnimID{AnimID::None};
    Animation& get();
    sf::IntRect& getFrame(int index = -1);
    void addAnimation(AnimID id_, int numFrames_, int x_, int y_, int w_, int h_);
};


using EntTuple = std::tuple<std::shared_ptr<PositionComponent>, std::shared_ptr<RenderableComponent>, std::shared_ptr<VelocityComponent>, std::shared_ptr<AnimationComponent>>;
