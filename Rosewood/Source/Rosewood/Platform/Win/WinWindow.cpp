#include "Pch.h"
#include "WinWindow.h"
#include "Win.h"

namespace rw
{
	namespace
	{
		static LRESULT CALLBACK WinWindowCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = 0;
			if (message == WM_DESTROY || message == WM_CLOSE)
			{
				::PostQuitMessage(0);
			}
			else
			{
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
	}
	Window* Window::RWCreateWindow(const WindowDefinition& windowDefinition)
	{
		return new WinWindow(windowDefinition);
	}

	WinWindow::WinWindow(const WindowDefinition& windowDefinition)
		: mDefinition(windowDefinition)
	{
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

		::RegisterClassEx(&windowClass);

		mHandle = ::CreateWindowEx(
			0,
			windowClass.lpszClassName,
			windowDefinition.Title.c_str(),
			windowStyle,
			0, 0,
			windowDefinition.Width, 
			windowDefinition.Height,
			nullptr, nullptr, instance, nullptr);
	}

	WinWindow::~WinWindow()
	{

	}

	void WinWindow::OnUpdate()
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	void WinWindow::SetEventCallback(const EventCallbackFn& eventCallback)
	{
		throw std::logic_error("The method or operation is not implemented.");
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