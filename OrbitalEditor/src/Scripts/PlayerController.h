#pragma once

#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Utils.h"

class PlayerController : public Orbital::Scriptable
{
public:
	PlayerController(const Entity& e) : Scriptable(e)
	{

	}

	virtual ~PlayerController() override
	{

	}

	virtual void onLoad()
	{

	}

	virtual void onStart()
	{

	}

	virtual void onUpdate(Orbital::Time t)
	{
		if (Inputs::IsKeyDown(OE_KEY_D))
			get<Orbital::Components::Transform>().Position()[0] += m_speed * t.seconds();
		if (Inputs::IsKeyDown(OE_KEY_A))
			get<Orbital::Components::Transform>().Position()[0] -= m_speed * t.seconds();
		if (Inputs::IsKeyDown(OE_KEY_W))
			get<Orbital::Components::Transform>().Position()[2] -= m_speed * t.seconds();
		if (Inputs::IsKeyDown(OE_KEY_S))
			get<Orbital::Components::Transform>().Position()[2] += m_speed * t.seconds();
	}

private:
	float m_speed = 0.3f;
};

