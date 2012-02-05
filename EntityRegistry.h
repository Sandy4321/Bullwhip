#pragma once
/*
Class for holding types of entitys, just to make it easy to access them via script
*/
//Will be replaced by Mineshaft resgistry
#include "Entity.h"
#include <map>
class EntityRegistry
{
    public:
        EntityRegistry() {};
        void AddFactory(std::string name, Entity* (*func)(int)) {factorys[name] = func;};
        Entity* NewEnt(std::string name) {return factorys[name](0);}
    protected:
    private:
        std::map<std::string, Entity* (*)(int)> factorys;
};

template<class T>
Entity* NewEnt(int i)
{
    return new T;
}
