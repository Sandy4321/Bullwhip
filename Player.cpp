#include "Player.h"

Player::Player()
{
    name = "player";
    attributes["teleport"] = true;
}

bool Player::onCollision(Entity* obj)
{
    if(obj->name == "phys_static" && (obj->GetY() - (obj->getspr().GetSize().y / 2)) > (GetY() + (draw.GetSize().y /2)))
    {
        can_jump = true;
    }
    return true;
}

void Player::jump()
{
    if(can_jump == true)
    {
        body->ApplyForce(Vec2(0.f, -53.f));
        can_jump = false;
    }
}

void Player::update(const sf::Input& in, SceneManager* scene)
{
    if(do_q)
    {
        SetX(xq);
        SetY(yq);
        do_q = false;
    }
    //movement
    if(in.IsKeyDown(sf::Key::Up))
    {
        jump();
    }
    if(in.IsKeyDown(sf::Key::Right))
    {
        body->ApplyForce(Vec2(5, 0));
    }
    if(in.IsKeyDown(sf::Key::Left))
    {
        body->ApplyForce(Vec2(-5, 0));
    }
    if((!in.IsKeyDown(sf::Key::Right)) && (!in.IsKeyDown(sf::Key::Left)))
    {
        body->SetLinearVelocity(Vec2(body->GetLinearVelocity().x* 0.90f, body->GetLinearVelocity().y));
    }
    Vec2 pos = body->GetPosition();
    float angle = body->GetAngle();
    draw.SetX(pos.x);
    draw.SetY(pos.y);
    draw.SetRotation(angle);
}

Entity* newPlayer(int i)
{
    return new Player;
}
