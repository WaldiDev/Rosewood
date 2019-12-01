#include "Pch.h"
#include "WinWindow.h"
#include "Win.h"

#include "Rosewood/Log.h"
#include "Rosewood/EventSystem/Event.h"
#include "Rosewood/EventSystem/ApplicationEvent.h"
#include "Rosewood/InputSystem/InputMapper.h"
#include "Rosewood/InputSystem/KeyboardKey.h"

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

		void RegisterRawHID(HWND windowHandle)
		{
			RAWINPUTDEVICE inputDevice	= {};
			inputDevice.usUsagePage		= 0x01;
			inputDevice.usUsage			= 0x06;
			inputDevice.dwFlags			= RIDEV_NOLEGACY; // do not generate legacy messages such as WM_KEYDOWN
			inputDevice.hwndTarget		= windowHandle;

			::RegisterRawInputDevices(&inputDevice, 1, sizeof(inputDevice));
		}
				
		bool ReadRawInput(HRAWINPUT lParam, VirtualKey& outVirtualKey, bool& outWasReleased)
		{
			char buffer[sizeof(RAWINPUT)] = {};
			UINT size = sizeof(RAWINPUT);
			::GetRawInputData(lParam, RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);
			if (raw->header.dwType != RIM_TYPEKEYBOARD)
			{
				return false;
			}

			const RAWKEYBOARD& rawKB = raw->data.keyboard;
			UINT virtualKey = rawKB.VKey;
			UINT scanCode = rawKB.MakeCode;
			UINT flags = rawKB.Flags;

			if (virtualKey == 255)
			{
				// discard "fake keys" which are part of an escaped sequence
				return false;
			}
			else if (virtualKey == VK_SHIFT)
			{
				// correct left-hand / right-hand SHIFT
				virtualKey = ::MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);
			}
			else if (virtualKey == VK_NUMLOCK)
			{
				// correct PAUSE/BREAK and NUM LOCK silliness, and set the extended bit
				scanCode = (::MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC) | 0x100);
			}

			// e0 and e1 are escape sequences used for certain special keys, such as PRINT and PAUSE/BREAK.
			// see http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
			const bool isE0 = ((flags & RI_KEY_E0) != 0);
			const bool isE1 = ((flags & RI_KEY_E1) != 0);

			if (isE1)
			{
				// for escaped sequences, turn the virtual key into the correct scan code using MapVirtualKey.
				// however, MapVirtualKey is unable to map VK_PAUSE (this is a known bug), hence we map that by hand.
				scanCode = (virtualKey == VK_PAUSE) ? 0x45 : MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
			}

			switch (virtualKey)
			{
				// right-hand CONTROL and ALT have their e0 bit set
			case VK_CONTROL:
				if (isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_RCONTROL;
				else
					virtualKey = (UINT)VirtualKey::RW_VK_LCONTROL;
				break;

			case VK_MENU:
				if (isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_RMENU;
				else
					virtualKey = (UINT)VirtualKey::RW_VK_LMENU;
				break;

				// NUMPAD ENTER has its e0 bit set
			case VK_RETURN:
				if (isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_SEPARATOR;
				break;

				// the standard INSERT, DELETE, HOME, END, PRIOR and NEXT keys will always have their e0 bit set, but the
				// corresponding keys on the NUMPAD will not.
			case VK_INSERT:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD0;
				break;

			case VK_DELETE:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_DECIMAL;
				break;

			case VK_HOME:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD7;
				break;

			case VK_END:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD1;
				break;

			case VK_PRIOR:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD9;
				break;

			case VK_NEXT:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD3;
				break;

				// the standard arrow keys will always have their e0 bit set, but the
				// corresponding keys on the NUMPAD will not.
			case VK_LEFT:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD4;
				break;

			case VK_RIGHT:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD6;
				break;

			case VK_UP:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD8;
				break;

			case VK_DOWN:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD2;
				break;

				// NUMPAD 5 doesn't have its e0 bit set
			case VK_CLEAR:
				if (!isE0)
					virtualKey = (UINT)VirtualKey::RW_VK_NUMPAD5;
				break;
			}
			
			// a key can either produce a "make" or "break" scancode. this is used to differentiate between down-presses and releases
			// see http://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
			outWasReleased = ((flags & RI_KEY_BREAK) != 0);
			outVirtualKey = static_cast<VirtualKey>(virtualKey);

			return true;

			// getting a human-readable string
			// UINT key = (scanCode << 16) | (isE0 << 24);
			// char nameBuffer[512] = {};
			// GetKeyNameTextA((LONG)key, nameBuffer, 512);
			// RW_CORE_INFO("KeyEvent: {0} wasReleased {1}", nameBuffer, wasReleased);
		}
	}

	Window* Window::RWCreateWindow(const WindowDefinition& windowDefinition)
	{
		return new WinWindow(windowDefinition);
	}

	WinWindow::WinWindow(const WindowDefinition& windowDefinition)
		: mDefinition(windowDefinition)
		, mHandle(nullptr)
		, mEventCallback(nullptr)
		, mInputMapper(nullptr)
	{
		mHandle = Win32CreateWindow(mDefinition);

		// Todo: This should be an assert
		if (!mHandle)
		{
			RW_CORE_ERROR("Win32CreateWindow failed: Return value wasn't valid");
		}

		RegisterRawHID(mHandle);
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
			case WM_INPUT:
			{
				VirtualKey virtualKey;
				bool wasReleased = false;
				if (ReadRawInput(reinterpret_cast<HRAWINPUT>(message.lParam), virtualKey, wasReleased))
				{
					mInputMapper->OnRawInputEvent(virtualKey, wasReleased);
				}

			} break;
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