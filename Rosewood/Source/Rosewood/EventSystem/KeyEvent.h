#pragma once

#include <sstream>

#include "Event.h"

namespace rw
{
	class ROSEWOOD_API KeyEvent : public Event
	{
	public:		
		inline int GetKeyCode() const { return mKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int keyCode)
			: mKeyCode(keyCode)
		{}

		int mKeyCode;
	};

	class ROSEWOOD_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode)
			, mRepeatCount(mRepeatCount)
		{}

		inline int GetRepeatCount() const { return mRepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int mRepeatCount;
	};

	class ROSEWOOD_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << mKeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

}
