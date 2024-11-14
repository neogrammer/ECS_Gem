#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>

// Base Classes
#include <tuple>
#include <assert.h>
#include <memory>

#include <ECS/ECSManager.h>







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
    ent->get<AnimationComponent>()->get().frameDelay = 2.f ;
    ent->get<AnimationComponent>()->get().setWaitToStart(true);
    ent->get<AnimationComponent>()->get().currentlyWaitingToStart = true;
    ent->get<AnimationComponent>()->get().startDelay = 30.f;


    RenderingSystem renderer{};
    AnimationSystem animator{};
    PhysicsSystem physics{};
    mgr.AddSystem(&renderer);
    mgr.AddSystem(&animator);
    mgr.AddSystem(&physics);

    sf::Clock timer{};
    float dt{};
	while (wnd.isOpen())
	{
		sf::Event e;
		while (wnd.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				wnd.close();
		}
        dt += timer.getElapsedTime().asSeconds();
        while (dt >= 1.f / 60.f)
        {
            mgr.Update(1.f / 60.f);

            wnd.clear();
            mgr.Render(1.f / 60.f);
            wnd.display();
            dt -= 1.f / 60.f;
        }
	}
}

