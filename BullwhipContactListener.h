#pragma once
#include <Box2D/Box2D.h>
#include <iostream>
#include "Entity.h"

class BullwhipContactListener : public b2ContactListener
{
    public:
        BullwhipContactListener();
        void BeginContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    protected:
    private:
};

