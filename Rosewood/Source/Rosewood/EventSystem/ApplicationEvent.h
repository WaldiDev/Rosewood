#pragma once

#include <sstream>

#include "Event.h"

namespace rw
{
	class ROSEWOOD_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: mWidth(width)
			, mHeight(height)
		{}

		inline unsigned int GetWidth() const { return mWidth; }
		inline unsigned int GetHeight() const { return mHeight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};

	class ROSEWOOD_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{}

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

}
