#include "windowBase.h"

namespace frame
{
	WindowBase::WindowBase(WindowInitSetting& initSetting) :
		exeInstance(initSetting.exeInstance), commandShow(initSetting.commandShow),
		windowTitleId(initSetting.windowTitleId), windowClassId(initSetting.windowClassId),
		windowStyle(initSetting.windowStyle), windowRect(initSetting.windowRect), parentWindowHandle(initSetting.parentWindowHandle)
	{
		// init() ‚Í”h¶æ‚ÅŒÄ‚Ô
	}

	WindowBase::~WindowBase()
	{
	}

	HINSTANCE WindowBase::getExeInstance()
	{
		return exeInstance;
	}

	HWND WindowBase::getWindowHandle()
	{
		return windowHandle;
	}

	HWND WindowBase::getParentWindowHandle()
	{
		return parentWindowHandle;
	}

	void WindowBase::init()
	{
		loadStrings();
		registerClass();
		create();
		show();
		run();
	}

	void WindowBase::loadStrings()
	{
		::LoadString(exeInstance, this->windowTitleId, this->windowTitle, MAX_LOAD_STRING);
		::LoadString(exeInstance, this->windowClassId, this->windowClass, MAX_LOAD_STRING);
	}

	void WindowBase::registerClass()
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = windowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = this->exeInstance;
		//wcex.hIcon = ::LoadIcon(this->exeInstance, MAKEINTRESOURCE(icon_id));
		wcex.hIcon = nullptr;
		wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)::GetStockObject(0);
		//wcex.lpszMenuName = MAKEINTRESOURCE(menu_id);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = this->windowClass;
		//wcex.hIconSm = ::LoadIcon(this->exeInstance, MAKEINTRESOURCE(icon_small_id));
		wcex.hIconSm = nullptr;

		::RegisterClassExW(&wcex);
	}

	void WindowBase::create()
	{
		this->windowHandle = ::CreateWindow(this->windowClass, this->windowTitle, this->windowStyle,
			this->windowRect.left, this->windowRect.top, this->windowRect.right - this->windowRect.left,
			this->windowRect.bottom - this->windowRect.top, this->parentWindowHandle, nullptr,
			this->exeInstance, nullptr);
	}

	void WindowBase::show()
	{
		::ShowWindow(this->windowHandle, this->commandShow);
		::UpdateWindow(this->windowHandle);
	}

	int WindowBase::run()
	{
		MSG message;
		while (::GetMessage(&message, nullptr, 0, 0)) {
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
		return 0;
	}

	LRESULT CALLBACK WindowBase::windowProc(HWND windowHandle, UINT message, WPARAM wParameter, LPARAM lParameter)
	{
		switch (message) {
			case WM_CREATE:
				break;
			case WM_COMMAND: {
				int commandId = LOWORD(wParameter);
				break;
			}
			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC dcHandle = ::BeginPaint(windowHandle, &ps);
				//...
				::EndPaint(windowHandle, &ps);
				break;
			}
			case WM_LBUTTONDOWN: {
				break;
			}
			case WM_CLOSE:
				break;
			case WM_DESTROY:
				::PostQuitMessage(0);
				break;
		}

		return ::DefWindowProc(windowHandle, message, wParameter, lParameter);
	}
}
