#include "Pch.h"
#include "InputMapper.h"

namespace rw
{
	namespace
	{
		size_t FindHashedNameForKey(const KeyLookupMap& lookupMap, KeyboardKey key)
		{
			KeyLookupMap::const_iterator it = lookupMap.find(key);
			return (it == lookupMap.end()) ? 0u : it->second;
		}
	}

	InputMapper::InputMapper()
		: mKeyState{ false }
	{

	}

	InputMapper::~InputMapper()
	{

	}

	rw::InputContext& InputMapper::CreateNewContext()
	{
		mContexts.push_back(InputContext());
		return mContexts.back();
	}

	void InputMapper::AddActionNameToKeyBinding(const char* name, const std::vector<KeyboardKey>& keys)
	{
		const size_t hashedName = std::hash<const char*>{}(name);

		for (const KeyboardKey key : keys)
		{
			mKeyLookupTable[key] = hashedName;
		}
	}

	void InputMapper::OnRawInputEvent(VirtualKey key, bool wasReleased)
	{
		const uint8_t keyId = static_cast<uint8_t>(key);
		bool& wasPressed = mKeyState[keyId];

		InputState inputState = InputState::Released;
		if (!wasReleased && !wasPressed)
		{
			inputState = InputState::Pressed;
		}
		else if (!wasPressed && wasPressed)
		{
			inputState = InputState::Repeated;
		}

		wasPressed = !wasReleased;
		ReactOnInputEvent(KeyboardKey(key), inputState);
	}

	void InputMapper::ReactOnInputEvent(KeyboardKey key, InputState state)
	{		
		const size_t hashedName = FindHashedNameForKey(mKeyLookupTable, key);
		if (hashedName == 0u)
		{
			return;
		}

		for (InputContext& context : mContexts)
		{	
			const InputBinding* binding = context.FindBinding(hashedName);
			if (!binding)
			{
				continue;
			}
						
			switch (state)
			{

			case rw::InputState::Pressed:
			{
				if (binding->mState == InputState::Pressed)
				{
					mCurrentActions.insert(binding);
					return;
				}
				if (binding->mState == InputState::Repeated)
				{
					mCurrentStates.insert(binding);
					return;
				}
			} break;

			case rw::InputState::Released:
			{
				if (binding->mState == InputState::Released)
				{
					mCurrentActions.insert(binding);
					return;
				}
				if (binding->mState == InputState::Repeated)
				{
					mCurrentStates.erase(binding);
					return;
				}
			} break;

			case rw::InputState::Repeated:
			default:
				break;
			}
		}
	}

	void InputMapper::Dispatch()
	{
		// Pressed and released actions
		for (const InputBinding* binding : mCurrentActions)
		{
			binding->mCallback();
		}
		mCurrentActions.clear();

		// States
		for (const InputBinding* binding : mCurrentStates)
		{
			binding->mCallback();
		}		
	}
}