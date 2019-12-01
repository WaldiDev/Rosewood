#pragma once

#include "Rosewood/Core.h"
#include "InputConstants.h"

namespace rw
{
	struct KeyboardKey
	{
		explicit KeyboardKey(VirtualKey key)
			: mKey(key)
		{}

		VirtualKey mKey;
	};

	struct KeyboardKeyHasher
	{
		std::size_t operator()(const KeyboardKey& key) const
		{
			return (std::hash<uint8_t>()(static_cast<uint8_t>(key.mKey)));
		}
	};

	inline bool operator==(const KeyboardKey& lhs, const KeyboardKey& rhs)
	{
		return (lhs.mKey == rhs.mKey);
	}

	inline bool operator!=(const KeyboardKey& lhs, const KeyboardKey& rhs) 
	{ 
		return !operator==(lhs, rhs); 
	}	
}