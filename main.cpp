#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>

// Base Classes
#include <tuple>
#include <assert.h>
#include <memory>

#include <ECS/ECSManager.h>


#define FPS60 1.f/60.f




int main()
{
    sf::RenderWindow wnd{ {1600U,900U,32U}, "Hello nurse", sf::Style::Close };
    ECSManager mgr{ wnd };

    auto ent = mgr.AddEntity();
    ent->addComponent<VelocityComponent>();
    ent->get<VelocityComponent>()->dx = 0.f;
    ent->get<VelocityComponent>()->dy = 0.f;

    ent->addComponent<PositionComponent>();
    ent->get<PositionComponent>()->x = 200.f;
    ent->get<PositionComponent>()->y = 400.f;

    sf::Texture playerTex;
    playerTex.loadFromFile("assets/textures/spritesheets/PlayerSheet.png");
    ent->addComponent<RenderableComponent>();
    ent->get<RenderableComponent>()->tex = &playerTex;

    ent->addComponent<AnimationComponent>();
    ent->get<AnimationComponent>()->addAnimation(AnimID::Idle, 16, 0, 0, 299, 240);
    ent->get<AnimationComponent>()->get(AnimID::Idle).frameDelay = 0.14f;
    ent->get<AnimationComponent>()->get(AnimID::Idle).setWaitToStart(true);
    ent->get<AnimationComponent>()->get(AnimID::Idle).currentlyWaitingToStart = true;
    ent->get<AnimationComponent>()->get(AnimID::Idle).setLooping(true);
    ent->get<AnimationComponent>()->get(AnimID::Idle).setStartDelay(2.f);

    ent->get<AnimationComponent>()->addAnimation(AnimID::Attack, 18, 0, 240*8, 299, 240);
    ent->get<AnimationComponent>()->get(AnimID::Attack).frameDelay = 0.f;
    ent->get<AnimationComponent>()->get(AnimID::Attack).setLooping(false);
    ent->get<AnimationComponent>()->get(AnimID::Attack).currentlyWaitingToStart = false;
    ent->get<AnimationComponent>()->get(AnimID::Attack).waitsToBegin = false;

    ent->get<AnimationComponent>()->addAnimation(AnimID::Run, 16, 0, 480*8, 299, 240);
    ent->get<AnimationComponent>()->get().frameDelay = 0.0f;

    ent->get<AnimationComponent>()->currAnimID = AnimID::Idle;

    ent->addComponent<PlayerControllerComponent>();
    ent->addComponent<AnimStateMachineComponent>();

    RenderingSystem renderer{};
    ControlSystem controller{};
    AnimationSystem animator{};
    AnimStateSystem machine{};
    PhysicsSystem physics{};
    mgr.AddSystem(&renderer);
    mgr.AddSystem(&controller);
    mgr.AddSystem(&physics);
    mgr.AddSystem(&machine);
    mgr.AddSystem(&animator);



    sf::Font font;
    font.loadFromFile("assets/fonts/font1.ttf");
    sf::Text fpsLabel;
    fpsLabel.setFont(font);
    fpsLabel.setString("  FPS");
    fpsLabel.setFillColor(sf::Color::White);
    fpsLabel.setOutlineThickness(2U);
    fpsLabel.setOutlineColor(sf::Color::Black);
    fpsLabel.setPosition({ 10.f,10.f });

    sf::Clock timer{};
    float dt{};
    int count{};
    float counter{};
    sf::Clock fpsTimer{};
	while (wnd.isOpen())
	{
		sf::Event e;
		while (wnd.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				wnd.close();
		}
        counter += timer.getElapsedTime().asSeconds();
        dt = timer.restart().asSeconds();
        if (counter >= 1.f)
        {
            counter = 0.f;
            std::string str = "";
            str = std::to_string(count);    
            str.append(" FPS");
            fpsLabel.setString(str);
            count = 0;
        }
        else
        {
            if (counter >= 1.f / 60.f)
            {
                count++;
            }
        }
      
        
        mgr.Update(dt);

        wnd.clear();
        mgr.Render(dt);
        wnd.draw(fpsLabel);
        wnd.display();
        
	}
}

