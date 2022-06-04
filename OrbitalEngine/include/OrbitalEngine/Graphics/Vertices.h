#pragma once
#pragma warning(push)
#pragma warning(disable : 4661)

#include "OrbitalEngine/Utils.h"


#define OE_ATTRIBUTE(name, count, ctype, oetype, normalized) \
	public: \
		static inline const std::string& getName() { return s_name; } \
		static inline size_t GetCount() { return count; } \
		static inline size_t GetSize() { return sizeof(ctype) * count; } \
		static inline unsigned int GetType() { return oetype; } \
		static inline unsigned int GetNormalized() { return normalized; } \
	private: \
		static inline const std::string& s_name = name;

namespace Orbital
{
	class VertexBuffer;

	struct Position3
	{
		glm::vec3 position;

		Position3() : position(0.0f, 0.0f, 0.0f) { }
		Position3(float x, float y, float z) : position(x, y, z) { }
		OE_ATTRIBUTE("a_Position", 3, float, OE_FLOAT, OE_FALSE)
	};

	struct Normal
	{
		glm::vec3 normal;

		Normal() : normal(0.0f, 0.0f, 0.0f) { }
		Normal(float x, float y, float z) : normal(x, y, z) { }
		OE_ATTRIBUTE("a_Normal", 3, float, OE_FLOAT, OE_FALSE)
	};

	struct Position2
	{
		glm::vec2 position;

		Position2() : position(0.0f, 0.0f) { }
		Position2(float x, float y) : position(x, y) { }
		OE_ATTRIBUTE("a_Position", 2, float, OE_FLOAT, OE_FALSE)
	};

	struct Color4
	{
		glm::vec4 color;

		Color4() : color(1.0f, 1.0f, 1.0f, 1.0f) { }
		Color4(float r, float g, float b, float a) : color(r, g, b, a) { }
		OE_ATTRIBUTE("a_Color", 4, float, OE_FLOAT, OE_FALSE)
	};

	struct Color3
	{
		glm::vec3 color;

		Color3() : color(1.0f, 1.0f, 1.0f) { }
		Color3(float r, float g, float b) : color(r, g, b) { }
		OE_ATTRIBUTE("a_Color", 3, float, OE_FLOAT, OE_FALSE)
	};

	struct TexCoords
	{
		glm::vec2 texCoords;

		TexCoords() : texCoords(0.0f, 0.0f) { }
		TexCoords(float x, float y) : texCoords(x, y) { }
		OE_ATTRIBUTE("a_TexCoords", 2, float, OE_FLOAT, OE_FALSE)
	};

	template<class... Bases>
	struct Vertex : Bases...
	{
		Vertex() : Bases()...
		{

		}

		Vertex(Bases... bases) : Bases(bases)...
		{
		}

		template <typename... Args>
		Vertex(Args... args) : Bases(args)...
		{
		}

		static size_t GetCount() { return (Bases::GetCount() + ...); }
		static size_t GetSize() { return (Bases::GetSize() + ...); }
		static unsigned int GetType() { return (Bases::GetType() + ...); }
		static unsigned int GetNormalized() { return (Bases::GetNormalized() + ...); }
		static Vertex<Bases...> Empty() { return Vertex<Bases...>(); }
	};

	template <class ...Vertices>
	class VertexContainer
	{
	public:
		template <class... T>
		VertexContainer(T&&... args) : mVertices({ args... }) { }
		VertexContainer(size_t count) : mVertices(count) { }

		void AllocateMemory(const VertexBuffer& buffer) const;
		void SubmitData(const VertexBuffer& buffer) const;

		void SetLayout(const VertexBuffer& buffer) const;
		void SetVertex(size_t i, Vertex<Vertices...>&& vertex) { mVertices[i] = vertex; }

		size_t GetCount() const { return mVertices.size(); }
		size_t GetSize() const { return mVertices.size() * Vertex<Vertices...>::GetSize(); }
		const void* GetData() const { return mVertices.data(); }
		const Vertex<Vertices...>* GetFirstVertex() const { return &mVertices[0]; }
		const Vertex<Vertices...>& operator[](size_t i) const { return mVertices[i]; }
		Vertex<Vertices...>& operator[](size_t i) { return mVertices[i]; }

		std::vector<Vertex<Vertices...>>::iterator begin() { return mVertices.begin(); }
		std::vector<Vertex<Vertices...>>::iterator end() { return mVertices.end(); }

	private:
		std::vector <Vertex<Vertices...>> mVertices;
	};

	// Vertices
	template struct Vertex<Position3, Color4, Normal, TexCoords>;
	using BasicVertex = Vertex<Position3, Color4, Normal, TexCoords>;

	// Containers
	template class VertexContainer<Position3, Color4, Normal, TexCoords>;
	using BasicVertexContainer = VertexContainer<Position3, Color4, Normal, TexCoords>;

}
#pragma warning(pop)
