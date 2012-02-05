#include "BoxDynamicBody.h"
#include "../Constants.h"
BoxDynamicBody::BoxDynamicBody()
{
    //ctor
    type = BODY_DYNAMIC;
}

void BoxDynamicBody::Intialize(Def d, Entity* obj)
{
    body_def.position.Set(d.GetVal<int>("x") * SCALE, d.GetVal<int>("y") * SCALE);
    body_def.angle = toRad(d.GetVal<float>("rotation"));
    body_def.userData = obj;
    body_def.type = b2_dynamicBody;
    bounding.SetAsBox( (d.GetVal<int>("hw")) * SCALE, (d.GetVal<int>("hh")) * SCALE);
    fix_def.density = 1.0f;
    fix_def.friction = 0.2f;
    fix_def.shape = &bounding;

    Def c;
    c.SetVal("def", body_def);
    body = (b2Body*)phys_world->CreateBody(c);
    fix = body->CreateFixture(&fix_def);
}
