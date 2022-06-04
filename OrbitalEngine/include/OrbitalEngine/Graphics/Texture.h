#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class TextureManager;

	struct TextureData
	{
		int width = 0;
		int height = 0;
		int nChannels = 0;
		unsigned int internalFormat = OE_RGB8;
		unsigned int format = OE_RGB;
		unsigned char* data = nullptr;
	};

	class Texture : public Asset
	{
	public:
		virtual ~Texture() {};

		static TextureData Load(const std::string& filename);
		virtual void Bind() const = 0;
		virtual void Bind(unsigned int slot) const = 0;
		virtual void Unbind() const = 0;

		virtual void SetWrapS(unsigned int value) = 0;
		virtual void SetWrapT(unsigned int value) = 0;
		virtual void SetMinFilter(unsigned int value) = 0;
		virtual void SetMagFilter(unsigned int value) = 0;

		unsigned int GetRendererId() const { return mRendererId; }
		unsigned int GetWidth() const { return mWidth; }
		unsigned int GetHeight() const { return mHeight; }
		unsigned int GetWrapS() const { return mWrapS; }
		unsigned int GetWrapT() const { return mWrapT; }
		unsigned int GetMinFilter() const { return mMinFilter; }
		unsigned int GetMagFilter() const { return mMagFilter; }

	protected:
		Texture(const std::string& tag, unsigned int width, unsigned int height)
			: Asset(sId,  tag), mRendererId(0), mWidth(width), mHeight(height)
			, mWrapS(0), mWrapT(0), mMinFilter(0), mMagFilter(0)
		{
			sId += 1;
		}
		static Texture* Create(
			const std::string& tag, unsigned int width, unsigned int height, unsigned char* data);
		static Texture* Create(
			const std::string& tag, TextureData texXata);

	protected:
		friend TextureManager;

		unsigned int mRendererId;
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mWrapS;
		unsigned int mWrapT;
		unsigned int mMinFilter;
		unsigned int mMagFilter;

		static inline size_t sId = 0;
	};
}