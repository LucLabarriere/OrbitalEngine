#pragma once

namespace Orbital
{
	class Asset
	{
	public:
		size_t GetId() const { return mId; }
		const std::string& GetTag() const { return mTag; }

		void SetTag(const std::string& tag) { mTag = tag; }

	protected:
		Asset(size_t id, const std::string& tag) : mId(id), mTag(tag) { }

	protected:
		size_t mId;
		std::string mTag;
	};
}