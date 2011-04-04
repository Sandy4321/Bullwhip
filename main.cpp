#include <iostream>
#include <string>
#include <math.h>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ScriptedEntity.h"
#include "InfoBox.h"
#include "JMath.h"
#include "Constants.h"
#include "entites/phys_dynamic.h"
#include "Player.h"
//Version is 0.09

using namespace std;
int main()
{
    Game& gam = Game::Instance();
    gam.init("Bullwhip.Platformer", 800, 600); //Window title, width, height
    gam.GetScene()->Init(b2Vec2(0.f, 10.f));
    SceneManager* scene = gam.GetScene();
    EntityRegistry* reg = gam.GetRegistry();
    reg->AddFactory("base_ent", &newEntity);
    reg->AddFactory("player", &newPlayer);

    scene->LoadScene("level.bin");


    Entity* player = reg->NewEnt("player");
    Def pdef;
    pdef.SetVal("x", 100);
    pdef.SetVal("y", 100);
    pdef.SetString("image", "player.png");
    player->init(pdef);
    scene->AddEntity(player);


    while(gam.run())
    {
        const sf::Input& in = gam.getin();


        sf::Event event;


        //Handle events
        while(gam.gEvent(event))
        {
            if(event.Type == sf::Event::Closed)
                gam.Quit();
        }
        gam.draw();
    }
    return 0;
}
