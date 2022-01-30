#pragma once

#define OE_ATTRIBUTE(name, count, ctype, oetype, normalized) \
	public: \
		static inline const std::string& getName() { return s_name; } \
		static inline unsigned int GetCount() { return count; } \
		static inline unsigned int GetSize() { return sizeof(ctype) * count; } \
		static inline unsigned int GetType() { return oetype; } \
		static inline unsigned int GetNormalized() { return normalized; } \
	private: \
		static inline const std::string& s_name = name;

namespace OrbitalEngine
{
	class VertexBuffer;

	struct Position3
	{
		glm::vec3 position;
		Position3(float x, float y, float z) : position(x, y, z) { }

		OE_ATTRIBUTE("a_Position", 3, float, OE_FLOAT, OE_FALSE)

	};

	struct Position2
	{
		glm::vec2 position;

		Position2(float x, float y) : position(x, y) { }
		OE_ATTRIBUTE("a_Position", 2, float, OE_FLOAT, OE_FALSE)
	};

	struct Color4
	{
		glm::vec4 color;

		Color4(float r, float g, float b, float a) : color(r, g, b, a) { }
		OE_ATTRIBUTE("a_Color", 4, float, OE_FLOAT, OE_FALSE)
	};

	struct Color3
	{
		glm::vec3 color;

		Color3(float r, float g, float b) : color(r, g, b) { }
		OE_ATTRIBUTE("a_Color", 3, float, OE_FLOAT, OE_FALSE)
	};

	template<class... Bases>
	struct Vertex : Bases...
	{
		Vertex(Bases... bases) : Bases(bases)...
		{
		}

		template <typename... Args>
		Vertex(Args... args) : Bases(args)...
		{
		}

		static unsigned int GetCount() { return (Bases::GetCount() + ...); }
		static unsigned int GetSize() { return (Bases::GetSize() + ...); }
		static unsigned int GetType() { return (Bases::GetType() + ...); }
		static unsigned int GetNormalized() { return (Bases::GetNormalized() + ...); }
	};

	template <class ...Vertices>
	class VertexContainer
	{

	public:
		template <class... T>
		VertexContainer(T&&... args) { m_vertices = { args... }; }
		void allocateMemory(const VertexBuffer& buffer) const;
		void setLayout(const VertexBuffer& buffer) const;

		unsigned int getCount() const { return m_vertices.size(); }
		unsigned int getSize() const { return m_vertices.size() * Vertex<Vertices...>::GetSize(); }
		const void* getData() const { return m_vertices.data(); }


	private:
		std::vector <Vertex<Vertices...>> m_vertices;
	};


	// Vertices
	template struct Vertex<Position3>;
	template struct Vertex<Position3, Color4>;
	//using BasicVertex = Vertex<Position3>;

	// Containers
	template struct VertexContainer<Position3, Color4>;
}
