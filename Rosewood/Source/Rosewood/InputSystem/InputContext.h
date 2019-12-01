#pragma once

#include "Rosewood/Core.h"

namespace rw
{
	using InputCallback = std::function<void()>;

	enum class InputState : uint8_t
	{
		Pressed,
		Released,
		Repeated
	};

	struct InputBinding
	{
		InputBinding()
			: mHashedName(0)
			, mState(InputState::Pressed)
			, mCallback(nullptr)
		{}

		InputBinding(const char* name, InputState state, InputCallback callback)
			: mHashedName(std::hash<const char*>{}(name))
			, mState(state)
			, mCallback(callback)
		{}
		
		bool HasName(const char* name)
		{
			return (mHashedName == std::hash<const char*>{}(name));
		}

		std::size_t mHashedName;

		InputState mState;

		InputCallback mCallback;
	};

	class InputContext
	{
	public:
		InputContext();
		~InputContext();

		// Adds an action to this context and returns it. If an action with this name already exist its callback gets overridden.
		InputBinding& AddBinding(const char* name, InputState state, const InputCallback& callback);

		const InputBinding* FindBinding(const char* name) const;
		const InputBinding* FindBinding(size_t hashedName) const;

	private:
		std::array<InputBinding, 32> mInputBindings;
		size_t mCurrentActions;

	};
}