#ifndef _windwoBase_h_
#define _windwoBase_h_

#include <Windows.h>
#include "frameConstants.h"
#include "windowInitSetting.h"

namespace frame
{
	// {abstract}
	class WindowBase
	{
		public:
			WindowBase(WindowInitSetting& initSetting);
			virtual ~WindowBase();
			HINSTANCE getExeInstance();
			HWND getWindowHandle();
			HWND getParentWindowHandle();
		protected:
			virtual int getWindowKey() = 0;
			virtual void init();
			virtual void create();
			virtual void show();
		private:
			void loadStrings();
			void registerClass();
			int run();

			static LRESULT CALLBACK windowProc(HWND windowHandle, UINT message, WPARAM wParameter, LPARAM lParameter);

			HINSTANCE exeInstance;
			int commandShow;
			HWND windowHandle;
			int windowTitleId;
			int windowClassId;
			DWORD windowStyle;
			RECT windowRect;
			HWND parentWindowHandle;

			wchar_t windowTitle[MAX_LOAD_STRING];
			wchar_t windowClass[MAX_LOAD_STRING];
	};
}

#endif // _windwoBase_h_
