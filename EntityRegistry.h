/**
 * @file EntityRegistry.h
 * @brief Factory controller for entites
 * @author neos300
 * @version 1.0
 * @date 2012-06-20
 */
#pragma once
#include "Entity.h"
#include <map>
class EntityRegistry
{
    public:
        EntityRegistry() {};
	/**
	 * @brief Adds a entity to the registry
	 *
	 * @param name The class of the entity
	 * @param func The factory function for that class
	 */
        void AddFactory(std::string name, Entity* (*func)(int)) {factorys[name] = func;};
	/**
	 * @brief Instantates a new entity
	 *
	 * @param name The class of the entity
	 *
	 * @return A pointer to the new entity
	 */
        Entity* NewEnt(std::string name) {return factorys[name](0);}
    protected:
    private:
        std::map<std::string, Entity* (*)(int)> factorys;
};

/**
 * @brief A factory function for entites. Instantate with &NewEnt<Entity>
 *
 * @tparam T The derived class of the entity
 * @param i A useless int required for some reason
 *
 * @return A pointer to the new entity
 */
template<class T>
Entity* NewEnt(int i)
{
    return new T;
}
