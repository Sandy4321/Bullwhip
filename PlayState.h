//General game setup and logic goes here (although in the future logic entites will take care of this)
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "SceneManager.h"
#include "EntityRegistry.h"
#include "entites/phys_dynamic.h"
#include "Player.h"
#include "entites/game_spawnpoint.h"
#include "entites/tele_coord.h"
#include "entites/tele_obj.h"
#include "entites/ent_string.h"
#include "SimpleINI/SimpleIni.h"
#include "entites/game_setglobal.h"
#include <Gwen/Controls/Button.h>

class PlayState : public State
{
    public:
        PlayState();
        virtual void Init(sf::RenderWindow* win);
        virtual std::string Update();
    protected:
        SceneManager* scene;
        EntityRegistry* reg;
        CSimpleIni bullwhipini;
        Entity* player;
        bool alive;
        sf::RenderTexture tex;
        sf::Sprite renderspr;
        Gwen::Controls::Button* play;
    private:
        typedef State super;
};

#endif // PLAYSTATE_H
