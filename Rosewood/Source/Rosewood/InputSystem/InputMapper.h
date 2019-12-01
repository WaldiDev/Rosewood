#pragma once

#include "Rosewood/Core.h"
#include "InputConstants.h"
#include "InputContext.h"
#include "KeyboardKey.h"

/*
Usage: 

InputContext characterContext;

characterContext.AddAction("Jump", &Character::Jump);
characterContext.AddState("MoveForward, &Character::MoveForward");

InputMapper->AddContext(characterContext);

*/

namespace rw
{
	class InputContext;
	
	using KeyLookupMap = std::unordered_map<KeyboardKey, size_t, KeyboardKeyHasher>;

	class InputMapper
	{
	public:
		InputMapper();
		~InputMapper();

		InputContext& CreateNewContext();

		void AddActionNameToKeyBinding(const char* name, const std::vector<KeyboardKey>& keys);

		void OnRawInputEvent(VirtualKey key, bool wasReleased);

		void ReactOnInputEvent(KeyboardKey key, InputState state);

		void Dispatch();

	private:	

		std::vector<InputContext> mContexts;

		KeyLookupMap mKeyLookupTable;

		std::set<const InputBinding*> mCurrentActions;
		std::set<const InputBinding*> mCurrentStates;		

		bool mKeyState[255];
	};
}