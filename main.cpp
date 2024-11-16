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
    ent->get<AnimationComponent>()->get(AnimID::Idle).frameDelay = 0.11f;
    ent->get<AnimationComponent>()->get(AnimID::Idle).setWaitToStart(true);
    ent->get<AnimationComponent>()->get(AnimID::Idle).currentlyWaitingToStart = true;
    ent->get<AnimationComponent>()->get(AnimID::Idle).setLooping(true);
    ent->get<AnimationComponent>()->get(AnimID::Idle).setStartDelay(3.f);

    ent->get<AnimationComponent>()->addAnimation(AnimID::Attack, 18, 0, 240*8, 299, 240);
    ent->get<AnimationComponent>()->get(AnimID::Attack).frameDelay = 0.04f;
    ent->get<AnimationComponent>()->get(AnimID::Attack).setLooping(true);
    ent->get<AnimationComponent>()->get(AnimID::Attack).currentlyWaitingToStart = false;
    ent->get<AnimationComponent>()->get(AnimID::Attack).waitsToBegin = false;
    ent->get<AnimationComponent>()->get(AnimID::Attack).setStartDelay(0.f);


    ent->get<AnimationComponent>()->addAnimation(AnimID::Run, 16, 0, 480*8, 299, 240);
    ent->get<AnimationComponent>()->get(AnimID::Run).frameDelay = 0.04f;
    ent->get<AnimationComponent>()->get(AnimID::Run).setLooping(true);
    ent->get<AnimationComponent>()->get(AnimID::Run).currentlyWaitingToStart = false;
    ent->get<AnimationComponent>()->get(AnimID::Run).waitsToBegin = false;
    ent->get<AnimationComponent>()->get(AnimID::Run).setStartDelay(0.f);

    std::array<int, 8> arr = { 16, };
 std::array<float, 8> arrFrameDelay1 = { 0.11f, };
    std::array<int, 8> arr2 = { 18, };
    std::array<float, 8> arrFrameDelay2 = { 0.04f, };
 std::array<float, 8> arrFrameDelay3 = { 0.04f, };

    for (int i = 0; i < 8; i++)
    {
        arr[i] = 16;
        arrFrameDelay1[i] = 0.11f;
        arr2[i]=18;
        arrFrameDelay2[i]=0.04f;
        arrFrameDelay3[i]=0.04f;
    }

    ent->get<AnimationComponent>()->addAnimationSet8(AnimID::Idle, arr, 0, 0, 299, 240);
    ent->get<AnimationComponent>()->setAnimNames(AnimID::Idle, "IdleState");
    ent->get<AnimationComponent>()->setAnimFrameDelays(AnimID::Idle, arrFrameDelay1);
    ent->get<AnimationComponent>()->setAnimStartWaits(AnimID::Idle, true, 3.f);

  

    ent->get<AnimationComponent>()->addAnimationSet8(AnimID::Attack, arr2, 0, 240 * 8, 299, 240);
    ent->get<AnimationComponent>()->setAnimNames(AnimID::Attack, "ShootingState");
    ent->get<AnimationComponent>()->setAnimFrameDelays(AnimID::Attack, arrFrameDelay2);
    ent->get<AnimationComponent>()->setAnimStartWaits(AnimID::Attack);
   // ent->get<AnimationComponent>()->setAnimLooping(AnimID::Attack, false);

    ent->get<AnimationComponent>()->addAnimationSet8(AnimID::Run, arr, 0, 480 * 8, 299, 240);
    ent->get<AnimationComponent>()->setAnimNames(AnimID::Run, "RunningState");
    ent->get<AnimationComponent>()->setAnimFrameDelays(AnimID::Run, arrFrameDelay3);
    ent->get<AnimationComponent>()->setAnimStartWaits(AnimID::Run);


    ent->get<AnimationComponent>()->currAnimID = AnimID::Idle;
    ent->get<AnimationComponent>()->currDir = Dir::S;

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
    mgr.AddSystem(&animator);
    mgr.AddSystem(&machine);



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

