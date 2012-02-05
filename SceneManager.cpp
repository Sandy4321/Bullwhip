#include "SceneManager.h"

SceneManager::SceneManager()
{
    //reg == NULL;
}

void SceneManager::AddEntity(Entity& ent)
{
    entites.insert(entites.end(), &ent);
    std::cout << "[scene] added entity\n";
}

void SceneManager::AddEntity(Entity* ent)
{
    entites.insert(entites.end(), ent);
    std::cout << "[scene] added entity\n";
}

void SceneManager::Update(sf::RenderTarget& win)
{
    phys_world->Step(1.f / 60.f);

    //Parse entites
    win.SetView(v);
    for(unsigned int i = 0; i < entites.size(); i++)
    {
        //Update entity
        entites[i]->update(this);
        entites[i]->Draw(win);
    }
    if(specents["center"] != NULL)
    {
        v.SetCenter(specents["center"]->GetX(), specents["center"]->GetY());
    }
    win.SetView(win.GetDefaultView());
}

void SceneManager::Init(Vec2 gravity)
{
    phys_world = new Physics2D;
    phys_world->Init(gravity);
    std::cout << "[scene][phys] intialized physics\n";
    v.SetSize(800, 600);
    v.SetCenter(100, 100);
    std::cout << "[scene] set views\n";
}


void SceneManager::Spawn(Entity& plyr, std::string spawnpoint)
{
    AddEntity(plyr);
    plyr.SetX(spawnpoints[spawnpoint]->GetX());
    plyr.SetY(spawnpoints[spawnpoint]->GetY());
}

void SceneManager::RemoveEntityFromList(std::string name)
{
    for(unsigned int i = 0; i < entites.size(); i++)
    {
        if(GetEntity(name) == entites[i])
        {
            entites.erase(entites.begin()+i);
            return;
        }
    }
}

void SceneManager::RemoveEntityFromList(Entity* ent)
{
    for(unsigned int i = 0; i < entites.size(); i++)
    {
        if(ent == entites[i])
        {
            entites.erase(entites.begin()+i);
            return;
        }
    }
}

void SceneManager::LoadScene(std::string filename)
{
    sf::Clock time;
    inFile file;
    file.OpenFile(filename);
    //READ HEADER
    //INT: ENGINE VERSION
    if(file.ReadInt() != 1)
    {
        //error out
        std::cout << "[scene] [WARN] Incompatible map version!\n";
        return;
    }
    //INT: GAME ID (not used yet)
    int gameID = file.ReadInt();
    gameID++;
    //STRING: MAPNAME
    std::string mapname = file.ReadString();
    std::cout << "[scene] loading map:" << mapname << std::endl;
    //PROPERTY LIST: WORLD PROPERTY'S
    while(true)
    {
        //BYTE: TYPE
        BYTE t = file.ReadByte();
        if(t == 0) //no type, end of list
        {
            break;
        }
        if(t == 1) //int
        {
            //STRING: NAME
            //INT: VALUE
            std::string h = file.ReadString();
            int i = file.ReadInt();
            worldprops.SetVal(h, i);
        }
        if(t == 2) //float
        {
            //STRING: NAME
            //FLOAT: VALUE
            std::string h = file.ReadString();
            float i = file.ReadFloat();
            worldprops.SetVal(h, i);
        }
        if(t == 3) //string
        {
            //STRING: NAME
            //string: VALUE
            std::string h = file.ReadString();
            std::string i = file.ReadString();
            worldprops.SetVal(h, i);
        }
    }
    while(true)
    {
        std::string type = file.ReadString();
        if(type == "")
        {
            break;
        }
        Entity* newent = reg->NewEnt(type);
        Def pdef;
        while(true)
        {
            //BYTE: TYPE
            BYTE t = file.ReadByte();
            if(t == 0) //no type, end of list
            {
                break;
            }
            if(t == 1) //int
            {
                //STRING: NAME
                //INT: VALUE
                std::string h = file.ReadString();
                int i = file.ReadInt();
                pdef.SetVal(h, i);
            }
            if(t == 2) //float
            {
                //STRING: NAME
                //FLOAT: VALUE
                std::string h = file.ReadString();
                float i = file.ReadFloat();
                pdef.SetVal(h, i);
            }
            if(t == 3) //string
            {
                //STRING: NAME
                //string: VALUE
                std::string h = file.ReadString();
                std::string i = file.ReadString();
                pdef.SetVal(h, i);
            }
        }
        newent->init(pdef);
        AddEntity(newent);
        if(pdef.GetVal<std::string>("name") != "")
        {
            SetEntity(pdef.GetVal<std::string>("name"), newent);
        }
        if(type == "game_spawnpoint")
        {
            AddSpawn(newent, pdef.GetVal<std::string>("name"));
        }
    }
    file.Close();
    std::cout << "[scene] Level loading took:" << time.GetElapsedTime() << std::endl;
}
