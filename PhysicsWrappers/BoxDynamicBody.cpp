#include "BoxDynamicBody.h"
#include "../Constants.h"
BoxDynamicBody::BoxDynamicBody()
{
    //ctor
    type = BODY_DYNAMIC;
}

void BoxDynamicBody::Intialize(Def d, Entity* obj)
{
    body_def.position.Set((int)d.GetVal("x") * SCALE, (int)d.GetVal("y") * SCALE);
    body_def.angle = toRad(d.GetFloat("rotation"));
    body_def.userData = obj;
    body_def.type = b2_dynamicBody;
    bounding.SetAsBox( ((int)d.GetVal("hw")) * SCALE, ((int)d.GetVal("hh")) * SCALE);
    fix_def.density = 1.0f;
    fix_def.friction = 0.2f;
    fix_def.shape = &bounding;

    Def c;
    c.SetVal("def", &body_def);
    body = (b2Body*)phys_world->CreateBody(c);
    fix = body->CreateFixture(&fix_def);
}
