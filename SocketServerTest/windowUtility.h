#ifndef _windowUtility_h_
#define _windowUtility_h_

#include <Windows.h>

namespace frame
{
	class WindowUtility
	{
		public:
			static const char * convertToText(unsigned int message);
			static void showErrorMessage(HWND windowHandle, LPCSTR text, LPCSTR caption);
	};
}

#endif // _windowUtility_h_
