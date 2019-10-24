#include "Pch.h"
#include "WinWindow.h"
#include "Win.h"

#include "Rosewood/Log.h"
#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/EventSystem/ApplicationEvent.h"

namespace rw
{
	namespace
	{
		static LRESULT CALLBACK WinWindowCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = 0;
			switch (message)
			{
				case WM_CLOSE:
				case WM_DESTROY:
				{
					::PostQuitMessage(0);
				} break;
				default:
					result = ::DefWindowProc(windowHandle, message, wParam, lParam);
			}

			return result;
		}

		DWORD GetWindowStyleFlags(WindowType type)
		{
			DWORD styleFlags = 0;

			switch (type)
			{
			case WindowType::None:
				break;
			case WindowType::Fullscreen:
				break;
			case WindowType::Windowed:
				styleFlags = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
				break;
			case WindowType::Resizeable:
				styleFlags = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_SIZEBOX;
				break;
			case WindowType::Borderless:
				break;
			default:
				break;
			}

			return styleFlags;
		}

		HWND Win32CreateWindow(const WindowDefinition& windowDefinition)
		{
			RW_CORE_TRACE("Start Win32CreateWindow");

			const DWORD windowStyle = GetWindowStyleFlags(windowDefinition.Type);

			HMODULE instance = ::GetModuleHandle(nullptr);

			WNDCLASSEX windowClass		= {};
			windowClass.style			= CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc		= WinWindowCallback;
			windowClass.hInstance		= instance;
			windowClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
			windowClass.lpszClassName	= windowDefinition.Title.c_str();
			windowClass.hCursor			= LoadCursor(nullptr, IDC_ARROW);
			windowClass.cbSize			= sizeof(WNDCLASSEX);

			if (::RegisterClassEx(&windowClass) == 0)
			{
				RW_CORE_ERROR("Error in Win32CreateWindow: RegisterClassEx failed");
				return nullptr;
			}

			HWND handle = ::CreateWindowEx(
				0,
				windowClass.lpszClassName,
				windowDefinition.Title.c_str(),
				windowStyle,
				0, 0,
				windowDefinition.Width, 
				windowDefinition.Height,
				nullptr, nullptr, instance, nullptr);

			RW_CORE_TRACE("Finished Win32CreateWindow");
			return handle;
		}
	}

	Window* Window::RWCreateWindow(const WindowDefinition& windowDefinition)
	{
		return new WinWindow(windowDefinition);
	}

	WinWindow::WinWindow(const WindowDefinition& windowDefinition)
		: mDefinition(windowDefinition)
		, mHandle(nullptr)
	{
		mHandle = Win32CreateWindow(mDefinition);

		// Todo: This should be an assert
		if (!mHandle)
		{
			RW_CORE_ERROR("Win32CreateWindow failed: Return value wasn't valid");
		}
	}

	WinWindow::~WinWindow()
	{
		
	}

	void WinWindow::OnUpdate()
	{
		MSG message = {};
		while (::PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
			case WM_QUIT:
			{
				WindowCloseEvent closeEvent;
				mEventCallback(closeEvent);
			} break;
			default:
				break;
			}			

			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	}

	void WinWindow::SetIsVSyncEnabled(bool isVSyncEnabled)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	bool WinWindow::GetIsVSyncEnabled() const
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
}