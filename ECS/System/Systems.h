#pragma once

#include <ECS/System.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

// Derived Systems
class PhysicsSystem : public System {
 
    bool isMovingDiagonal(Entity& owner_);
    bool currentlyLettingGo{ false };
    float letgoElapsed{ 0.f };
    float letgoDelay{ 0.05f };

public:
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class AnimationSystem : public System {
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class RenderingSystem : public System {
public:
    sf::View* gameView;
    void Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime) override;
    void setView(sf::View& view_);
};
class ControlSystem : public System {
public:
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class AnimStateSystem : public System {
public:


    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
};
class MapSystem : public System {
public:
    sf::View* gameView;
    std::vector<sf::IntRect> tilesetTiles;
    sf::Vector2i tilesetSize{ 0,0 };
    sf::Texture tilesetTex{};
    std::vector<int> mapTiles;
    sf::Vector2f mapOffset{ 0.f, 0.f};
    sf::Vector2i mapSize{ 40,40 };
    sf::Vector2f tileSize{ 128.f,128.f };
    sf::RenderTexture renderedImage{};
    void Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_) override;
    void Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime) override;
    void setMap(std::string mapFilename_);
    void setView(sf::View& view_);
    void setupTileset(std::string tilesetFilename_);
    sf::Vector2f toISO(float x_, float y_);

};
