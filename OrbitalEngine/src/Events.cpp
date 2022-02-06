#include "OrbitalEngine/Events/Events.h"

std::ostream& operator<<(std::ostream& os, const OrbitalEngine::Event& e)
{
	os << e.toString();
	return os;
}