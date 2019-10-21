#pragma once

#include "Rosewood/Core.h"
#include "Rosewood/Window.h"

struct HWND__;
typedef HWND__* HWND;

namespace rw
{
	class WinWindow : public Window
	{
	public:
		explicit WinWindow(const WindowDefinition& windowDefinition);
		virtual ~WinWindow();

		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() const override { return mDefinition.Width; }
		virtual unsigned int GetHeight() const override { return mDefinition.Height; }

		virtual void SetEventCallback(const EventCallbackFn& eventCallback) override;

		virtual void SetIsVSyncEnabled(bool isVSyncEnabled) override;
		virtual bool GetIsVSyncEnabled() const override;

	private:
		WindowDefinition mDefinition;

		HWND mHandle;
	};
}
