#pragma once

#include "Rosewood/Core.h"

namespace rw
{
	enum class WindowType
	{
		None = 0,
		Fullscreen,
		Windowed,
		Resizeable,
		Borderless
	};

	struct WindowDefinition
	{
	public:
		WindowDefinition()
			: Type(WindowType::Resizeable)
			, Title(L"Rosewood Engine")
			, Width(1280u)
			, Height(720u)
		{}

		WindowDefinition(WindowType type, const std::wstring& title, unsigned int width, unsigned int height)
			: Type(type)
			, Title(title)
			, Width(width)
			, Height(height)
		{}

		WindowType Type;
		std::wstring Title;
		unsigned int Width;
		unsigned int Height;		
	};

	class Event;

	class ROSEWOOD_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void* GetHandle() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& eventCallback) = 0;

		virtual void SetIsVSyncEnabled(bool isVSyncEnabled) = 0;
		virtual bool GetIsVSyncEnabled() const = 0;

		static Window* RWCreateWindow(const WindowDefinition& windowDefinition);
	};
}
