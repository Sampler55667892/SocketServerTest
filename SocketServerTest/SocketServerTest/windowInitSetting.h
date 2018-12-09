#ifndef _windowSetting_h_
#define _windowSetting_h_

#include <Windows.h>

namespace frame
{
	struct WindowInitSetting
	{
		public:
			HINSTANCE exeInstance;
			int commandShow;
			int windowTitleId;
			int windowClassId;
			DWORD windowStyle;
			RECT windowRect;
			HWND parentWindowHandle;

			WindowInitSetting(HINSTANCE exeInstance, int commandShow, int windowTitleId, int windowClassId,
				DWORD windowStyle, RECT windowRect, HWND parentWindowHandle) :
				exeInstance(exeInstance), commandShow(commandShow),
				windowTitleId(windowTitleId), windowClassId(windowClassId),
				windowStyle(windowStyle), windowRect(windowRect), parentWindowHandle(parentWindowHandle)
			{
			}
	};
}

#endif // _windowSetting_h_
