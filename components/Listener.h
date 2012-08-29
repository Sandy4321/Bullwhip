#pragma once
#include "Cistron.h"

class Listener : public Cistron::Component
{
	public:
		Listener() : Cistron::Component("Listener") {};

		void addedToObject()
		{
			requestMessage("getx", &Listener::SetX);
			requestMessage("gety", &Listener::SetY);
			requestMessage("getrot", &Listener::SetRot);
			x = 0;
			y = 0;
		}

		
		void SetX(const Cistron::Message& msg)
		{
			x = boost::any_cast<int>(msg.p);
		}
		void SetY(const Cistron::Message& msg)
		{
			y = boost::any_cast<int>(msg.p);
		}
		void SetRot(const Cistron::Message& msg)
		{
			angle = boost::any_cast<float>(msg.p);
		}
		int GetX()
		{
			sendLocalMessage("sendpos");
			return x;
		}
		int GetY()
		{
			sendLocalMessage("sendpos");
			return y;
		}
	public:
		int x;
		int y;
		float angle;
};
