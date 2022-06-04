#include "OrbitalEngine/Events/MainEvents.h"

std::ostream& operator<<(std::ostream& os, const Orbital::Event& e)
{
	os << e.ToString();
	return os;
}