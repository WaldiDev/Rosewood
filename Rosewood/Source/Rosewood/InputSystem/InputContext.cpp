#include "Pch.h"
#include "InputContext.h"

namespace rw
{
	InputContext::InputContext()
		: mCurrentActions(0)
	{

	}

	InputContext::~InputContext()
	{

	}

	InputBinding& InputContext::AddBinding(const char* name, InputState state, const InputCallback& callback)
	{
		for (size_t i = 0; i < mCurrentActions; ++i)
		{
			InputBinding& action = mInputBindings[i];
			if (action.HasName(name))
			{
				action.mState = state;
				action.mCallback = callback;
				return action;
			}
		}

		InputBinding& binding = mInputBindings[mCurrentActions++];
		binding = InputBinding(name, state, callback);
		return binding;
	}

	const InputBinding* InputContext::FindBinding(const char* name) const
	{
		size_t hashedName = std::hash<const char*>{}(name);
		return FindBinding(hashedName);
	}

	const InputBinding* InputContext::FindBinding(size_t hashedName) const
	{
		for (size_t i = 0; i < mCurrentActions; ++i)
		{
			if (mInputBindings[i].mHashedName == hashedName)
			{
				return &mInputBindings[i];
			}
		}

		return nullptr;
	}
}