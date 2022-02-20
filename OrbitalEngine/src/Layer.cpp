#include "OrbitalEngine/Logic/Layer.h"

namespace OrbitalEngine
{
	Layer::Layer(const std::string& tag)
		: m_tag(tag)
	{

	}

	void Layer::play()
	{
		if (m_state == State::Running)
			Logger::Debug("Can't play an already running layer");
		else if (m_state == State::Stopped)
			Logger::Debug("Can't play a stopped layer");

		m_state = State::Running;
	}

	void Layer::pause()
	{
		if (m_state == State::Paused)
			Logger::Debug("Can't pause an already running layer");
		else if (m_state == State::Stopped)
			Logger::Debug("Can't pause a stopped layer");

		m_state = State::Paused;
	}

	void Layer::stop()
	{
		m_state = State::Stopped;
	}
}