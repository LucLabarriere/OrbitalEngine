#include "OrbitalEngine/Core.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

#define OE_ATTRIBUTE_NAME(str) \
	public: \
		static const std::string& getName() { return s_name; } \
	private: \
		static inline const std::string& s_name = str 

struct Position3
{
	glm::vec3 position;

	Position3(float x, float y, float z) : position(x, y, z) { }
	static unsigned int GetCount() { return 3;  }
	static unsigned int GetSize() { return sizeof(float) * 3; }
	OE_ATTRIBUTE_NAME("a_Position");
};

struct Position2
{
	glm::vec2 position;

	Position2(float x, float y) : position(x, y) { }
	static unsigned int GetCount() { return 2; }
	static unsigned int GetSize() { return sizeof(float) * 2; }
	OE_ATTRIBUTE_NAME("a_Position");
};

struct Color4
{
	glm::vec4 color;

	Color4(float r, float g, float b, float a) : color(r, g, b, a) { }
	static unsigned int GetCount() { return 4; }
	static unsigned int GetSize() { return sizeof(float) * 4; }
	OE_ATTRIBUTE_NAME("a_Color");
};

struct Color3
{
	glm::vec3 color;

	Color3(float r, float g, float b) : color(r, g, b) { }
	static unsigned int GetCount() { return 4; }
	static unsigned int GetSize() { return sizeof(float) * 4; }
	OE_ATTRIBUTE_NAME("a_Color");
};

template<class... Bases>
struct Vertex: Bases...
{
	Vertex(Bases... bases) : Bases(bases)...
	{
		std::cout << "Constructor" << std::endl;
	}

	template <typename... Args>
	Vertex(Args... args) : Bases(args)...
	{
		std::cout << "Constructor" << std::endl;
	}

	static unsigned int GetCount() { return (Bases::GetCount() + ...); }
	static unsigned int GetSize() { return (Bases::GetSize() + ...); }
};

template <class ...Vertices>
class VertexContainer
{

public:
	template <class... T>
	VertexContainer(T&&... args)
	{
		m_vertices = { args... };
		std::cout << "Size: " << m_vertices.size() << std::endl;

		for (const auto& vertex : m_vertices)
			std::cout << vertex.GetCount() << " ";

		std::cout << std::endl;
	}

private:
	std::vector <Vertex<Vertices...>> m_vertices;
};

int main()
{
	/*using V1 = Vertex<Position2, Color4>;
	using V2 = Vertex<Position3, Color4>;
	V1 vertex1({ 0.5f, 0.5f }, { 0.6f, 0.6f, 0.6f, 0.6f });
	V2 vertex2({ 0.5f, 0.5f, 0.5f}, { 0.6f, 0.6f, 0.6f, 0.6f });

	VertexContainer<Position3, Color4> container(
		vertex2,
		vertex2,
		vertex2
	);*/


	OrbitalEngine::Application app;
	app.run();

	/*VertexContainer<Position3, Color4> vertices(
		{{0.5f, 0.5f, 0.5f}, {0.1f, 0.2f, 0.3f, 1.0f}}
	);*/

	/*VertexBuffer vbo(0, vertices);
	VertexBuffer vbo2(0, vertices2);*/

	//Vertex<Position3, Color> vertex4({ 0.5f, 0.5f, 0.5f}   , {0.5f, 0.5f, 0.5f, 0.5f} );

	//Vertex<Position3, Color> vertex2 = { 0.5f, 0.5f, 0.5f  , 0.5f, 0.5f, 0.5f, 0.5f };
	//Vertex<Position3, Color> vertex3(0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);

	return 0;
}