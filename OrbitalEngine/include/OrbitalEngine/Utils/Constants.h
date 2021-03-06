#pragma once

#if defined (ORBITAL_OPENGL)
#define OE_FALSE GL_FALSE
#define OE_TRUE GL_TRUE

#define OE_FLOAT GL_FLOAT

#define OE_STATIC_DRAW GL_STATIC_DRAW
#define OE_DYNAMIC_DRAW GL_DYNAMIC_DRAW

#define OE_TRIANGLES GL_TRIANGLES

#define OE_LINEAR GL_LINEAR
#define OE_NEAREST GL_NEAREST
#define OE_REPEAT GL_REPEAT
#define OE_MIRRORED_REPEAT GL_MIRRORED_REPEAT
#define OE_CLAMP_TO_EDGE GL_CLAMP_TO_EDGE
#define OE_CLAMP_TO_BORDER GL_CLAMP_TO_BORDER
#define OE_LAST_LAYER 31

#define OE_RGB8 GL_RGB8
#define OE_RGBA8 GL_RGBA8
#define OE_RGB GL_RGB
#define OE_RGBA GL_RGBA

#endif

namespace Orbital
{
	enum class RenderMode
	{
		STATIC_BATCHED = 0,
		STATIC_NOT_BATCHED,
		DYNAMIC_BATCHED,
		DYNAMIC_NOT_BATCHED,
	};
}
